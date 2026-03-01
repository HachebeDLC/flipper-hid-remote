// Flipper Zero Web Bluetooth implementation

const FLIPPER_SERIAL_SERVICE_UUID = '8fe5b3d5-2e7f-4a98-2a48-7acc60fe0000';
const FLIPPER_SERIAL_RX_UUID = '19ed82ae-ed21-4c9d-4145-228e62fe0000'; // Write to Flipper
const FLIPPER_SERIAL_TX_UUID = '19ed82ae-ed21-4c9d-4145-228e61fe0000'; // Read from Flipper

let flipperRxCharacteristic = null;

async function connectToFlipper() {
    try {
        console.log('Searching for Flipper...');
        const device = await navigator.bluetooth.requestDevice({
            acceptAllDevices: true,
            optionalServices: [FLIPPER_SERIAL_SERVICE_UUID]
        });

        console.log(`Found: ${device.name}. Connecting...`);
        const server = await device.gatt.connect();

        console.log('GATT Connected. Fetching services...');
        const service = await server.getPrimaryService(FLIPPER_SERIAL_SERVICE_UUID);

        console.log('Getting Characteristics...');
        flipperRxCharacteristic = await service.getCharacteristic(FLIPPER_SERIAL_RX_UUID);
        
        console.log('Connected!');
        return true;
    } catch (error) {
        console.error('Bluetooth error:', error);
        return false;
    }
}

async function sendKeyToFlipper(key) {
    if (!flipperRxCharacteristic) {
        console.error('Not connected!');
        return;
    }

    try {
        // Our protocol: [0x01 (Type: Keyboard), char key]
        const data = new Uint8Array([0x01, key.charCodeAt(0)]);
        
        console.log(`Sending RAW HID packet for key "${key}"...`);
        
        // Flipper Serial expects Writes Without Response for high-speed serial data
        if (flipperRxCharacteristic.properties.writeWithoutResponse) {
             await flipperRxCharacteristic.writeValueWithoutResponse(data);
        } else {
             await flipperRxCharacteristic.writeValue(data);
        }
        
        console.log('Sent!');
    } catch (error) {
        console.error('Failed to send key!', error);
    }
}

// Export for testing
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { connectToFlipper, sendKeyToFlipper };
}
