// Flipper Zero Momentum/Xtreme Serial Service UUIDs
const FLIPPER_SERIAL_SERVICE_UUID = '8fe5b3d5-2e7f-4a98-2a48-7acc60fe0000';
const FLIPPER_SERIAL_RX_UUID = '19ed82ae-ed21-4c9d-bec7-eccb12341234'; // Based on common Momentum pattern
const FLIPPER_SERIAL_TX_UUID = '10203040-5060-7080-90a0-b0c0d0e0f010';

let flipperRxCharacteristic = null;

async function connectToFlipper() {
    try {
        console.log('Searching for HID Remote devices...');
        
        const device = await navigator.bluetooth.requestDevice({
            filters: [
                { namePrefix: 'HID_' }
            ],
            optionalServices: [FLIPPER_SERIAL_SERVICE_UUID, 'battery_service']
        });

        console.log(`Found: ${device.name}. Connecting...`);
        const server = await device.gatt.connect();

        console.log('Fetching Primary Service...');
        await new Promise(r => setTimeout(r, 500));
        
        const services = await server.getPrimaryServices();
        console.log("Found services:", services.map(s => s.uuid));
        
        const service = services.find(s => s.uuid === FLIPPER_SERIAL_SERVICE_UUID);
        if (!service) throw new Error("Could not locate Serial Service on Flipper.");

        console.log('Getting Characteristics...');
        const characteristics = await service.getCharacteristics();
        console.log("Available characteristics:", characteristics.map(c => c.uuid));
        
        // We'll pick the first writable characteristic found if our specific RX UUID fails
        flipperRxCharacteristic = characteristics.find(c => c.properties.writeWithoutResponse || c.properties.write);
        
        if (!flipperRxCharacteristic) throw new Error("No writable characteristic found.");

        console.log(`Connected to Characteristic: ${flipperRxCharacteristic.uuid}`);
        return true;
    } catch (error) {
        console.error('Bluetooth error:', error);
        alert("Connection Failed: " + error.message);
        return false;
    }
}

async function sendData(data) {
    if (!flipperRxCharacteristic) return;
    try {
        await flipperRxCharacteristic.writeValueWithoutResponse(data);
    } catch (e) {
        await flipperRxCharacteristic.writeValue(data);
    }
}

async function sendKeyToFlipper(key) {
    const data = new Uint8Array([0x01, key.charCodeAt(0)]);
    await sendData(data);
}

async function sendKeyDownToFlipper(hidCode) {
    const data = new Uint8Array([0x03, hidCode]);
    await sendData(data);
}

async function sendKeyUpToFlipper(hidCode) {
    const data = new Uint8Array([0x04, hidCode]);
    await sendData(data);
}

async function sendModifiersToFlipper(mask) {
    const data = new Uint8Array([0x05, mask]);
    await sendData(data);
}

async function sendMousePosToFlipper(dx, dy) {
    const data = new Uint8Array([0x02, dx & 0xFF, dy & 0xFF]);
    await sendData(data);
}

async function sendMouseButtonToFlipper(mask) {
    const data = new Uint8Array([0x06, mask]);
    await sendData(data);
}

async function sendMouseScrollToFlipper(delta) {
    const data = new Uint8Array([0x07, delta & 0xFF]);
    await sendData(data);
}
