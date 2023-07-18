// vite.config.js
import { defineConfig } from 'vite'
import {CustomHmr} from "./plugins/CustomHMR.js";
export default defineConfig({
    server: {
        port: 8000,
        host: true
    },
    preview: {
        port: 8000,
    },
    plugins: [CustomHmr()]
})
