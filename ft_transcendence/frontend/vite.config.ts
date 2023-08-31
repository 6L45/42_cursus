import { sveltekit } from '@sveltejs/kit/vite';
import { defineConfig } from 'vitest/config';

export default defineConfig({
    plugins: [sveltekit()],
    server: {
        port: 8080,
        proxy: {
            '/api': "http://backend:3000",
            '/ws' : "http://backend:3001",
        },
    },
    preview: {
        port: 8080,
        proxy: {
            '/api': "http://backend:3000",
            '/ws' : "http://backend:3001",
        },
    },
    test: {
        include: ['src/**/*.{test,spec}.{js,ts}']
    }
});
