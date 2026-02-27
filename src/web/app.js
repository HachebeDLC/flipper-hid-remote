// Flipper Zero Web Bluetooth implementation

async function connectToFlipper() {
    try {
        console.log('Requesting Bluetooth Device...');
        const device = await navigator.bluetooth.requestDevice({
            filters: [{ namePrefix: 'Flipper' }],
            optionalServices: ['0000180a-0000-1000-8000-00805f9b34fb'] // Dummy service UUID
        });

        console.log('Connecting to GATT Server...');
        const server = await device.gatt.connect();

        console.log('Getting Service...');
        const service = await server.getPrimaryService('0000180a-0000-1000-8000-00805f9b34fb');

        console.log('Getting Characteristic...');
        const characteristic = await service.getCharacteristic('00002a29-0000-1000-8000-00805f9b34fb');

        console.log('Connected!');
        return true;
    } catch (error) {
        console.error('Connection failed!', error);
        return false;
    }
}

// Export for testing
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { connectToFlipper };
}
