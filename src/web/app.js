// Flipper Zero Official Serial Service UUIDs (Nordic UART)
const FLIPPER_SERIAL_SERVICE_UUID = '6e400001-b5a3-f393-e0a9-e50e24dcca9e';
const FLIPPER_SERIAL_RX_UUID = '6e400002-b5a3-f393-e0a9-e50e24dcca9e'; // Write
const FLIPPER_SERIAL_TX_UUID = '6e400003-b5a3-f393-e0a9-e50e24dcca9e'; // Read

let flipperRxCharacteristic = null;

async function connectToFlipper() {
    try {
        console.log('Searching for HID Remote devices...');
        
        const device = await navigator.bluetooth.requestDevice({
            filters: [
                { namePrefix: 'HID_' }   // Our Momentum custom name
            ],
            optionalServices: [FLIPPER_SERIAL_SERVICE_UUID, 'battery_service']
        });

        console.log(`Found: ${device.name}. Connecting...`);
        const server = await device.gatt.connect();

        console.log('Fetching Primary Service...');
        // We try a small delay to let GATT DB populate
        await new Promise(r => setTimeout(r, 500));
        
        let service;
        try {
            service = await server.getPrimaryService(FLIPPER_SERIAL_SERVICE_UUID);
        } catch (e) {
            console.warn("NUS Service not found by UUID, trying generic search...");
            const services = await server.getPrimaryServices();
            console.log("Available services:", services.map(s => s.uuid));
            service = services.find(s => s.uuid === FLIPPER_SERIAL_SERVICE_UUID);
        }

        if (!service) throw new Error("Could not locate Serial Service on Flipper.");

        console.log('Getting RX Characteristic...');
        flipperRxCharacteristic = await service.getCharacteristic(FLIPPER_SERIAL_RX_UUID);
        
        console.log('Connected Successfully!');
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
        console.warn("Retrying with response...");
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
