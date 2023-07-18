export function CustomHmr() {
    return {
        name: 'custom-hmr',
        enforce: 'post',
        // HMR
        handleHotUpdate({ file, server }) {
            if (file.endsWith('.txt')) {
                console.log('reloading json file...');

                server.ws.send({
                    type: 'full-reload',
                    path: '*'
                });
            }
        },
    }
}
