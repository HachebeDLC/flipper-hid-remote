// Flipper Zero Momentum/Xtreme Serial Service UUIDs
const FLIPPER_SERIAL_SERVICE_UUID = '8fe5b3d5-2e7f-4a98-2a48-7acc60fe0000';

let flipperRxCharacteristic = null;
let reconnectAttempts = 0;

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

        // 1. STABILITY DELAY: Give the Flipper time to handle bonding
        console.log('Waiting for connection stability...');
        await new Promise(r => setTimeout(r, 1000));
        
        if (!device.gatt.connected) {
            throw new Error("GATT Server disconnected during handshake.");
        }

        console.log('Fetching Primary Services...');
        const services = await server.getPrimaryServices();
        console.log("Found services:", services.map(s => s.uuid));
        
        const service = services.find(s => s.uuid === FLIPPER_SERIAL_SERVICE_UUID);
        if (!service) throw new Error("Could not locate Serial Service on Flipper.");

        console.log('Getting Characteristics...');
        const characteristics = await service.getCharacteristics();
        console.log("Available characteristics:", characteristics.map(c => c.uuid));
        
        // Pick the first writable characteristic
        flipperRxCharacteristic = characteristics.find(c => c.properties.writeWithoutResponse || c.properties.write);
        
        if (!flipperRxCharacteristic) throw new Error("No writable characteristic found.");

        console.log(`Connected Successfully to ${flipperRxCharacteristic.uuid}`);
        reconnectAttempts = 0; // Reset on success
        return true;
    } catch (error) {
        console.error('Bluetooth error:', error);
        
        // 2. AUTO-RETRY LOGIC: Handle the "Bonding Disconnect" automatically
        if ((error.name === 'NetworkError' || error.message.includes('disconnected')) && reconnectAttempts < 2) {
            reconnectAttempts++;
            console.warn(`Connection dropped (likely bonding). Retrying attempt ${reconnectAttempts}...`);
            await new Promise(r => setTimeout(r, 500));
            return connectToFlipper(); // Recursive retry
        }

        alert("Connection Failed: " + error.message);
        reconnectAttempts = 0;
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
