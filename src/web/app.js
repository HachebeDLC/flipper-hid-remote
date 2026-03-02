// Flipper Zero Momentum/Xtreme Serial Service UUIDs
const FLIPPER_SERIAL_SERVICE_UUID = '8fe5b3d5-2e7f-4a98-2a48-7acc60fe0000';
const FLIPPER_SERIAL_RX_UUID = '19ed82ae-ed21-4c9d-4145-228e62fe0000'; // Explicit RX

let flipperRxCharacteristic = null;
let reconnectAttempts = 0;

async function connectToFlipper() {
    try {
        console.log('Searching for HID Remote devices...');
        
        const device = await navigator.bluetooth.requestDevice({
            filters: [{ namePrefix: 'HID_' }],
            optionalServices: [FLIPPER_SERIAL_SERVICE_UUID, 'battery_service']
        });

        console.log(`Found: ${device.name}. Connecting...`);
        const server = await device.gatt.connect();

        console.log('Waiting for connection stability...');
        await new Promise(r => setTimeout(r, 1200));
        
        if (!device.gatt.connected) throw new Error("GATT disconnected during handshake.");

        console.log('Fetching Primary Service...');
        const service = await server.getPrimaryService(FLIPPER_SERIAL_SERVICE_UUID);

        console.log('Getting RX Characteristic...');
        // We target the specific working RX UUID
        flipperRxCharacteristic = await service.getCharacteristic(FLIPPER_SERIAL_RX_UUID);
        
        console.log(`Connected Successfully!`);
        reconnectAttempts = 0;
        return true;
    } catch (error) {
        console.error('Bluetooth error:', error);
        
        if ((error.name === 'NetworkError' || error.message.includes('disconnected')) && reconnectAttempts < 2) {
            reconnectAttempts++;
            console.warn(`Retrying connection (${reconnectAttempts})...`);
            await new Promise(r => setTimeout(r, 800));
            return connectToFlipper();
        }

        alert("Connection Failed: " + error.message);
        reconnectAttempts = 0;
        return false;
    }
}

async function sendData(data) {
    if (!flipperRxCharacteristic) return;
    try {
        // NUS RX expects Write Without Response
        await flipperRxCharacteristic.writeValueWithoutResponse(data);
    } catch (e) {
        console.warn("Write error, retrying with response...", e);
        try { await flipperRxCharacteristic.writeValue(data); } catch(e2) { console.error("Critical write fail", e2); }
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
