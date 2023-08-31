#!/bin/bash

set -e
export PORT=8080
npm upgrade
npm install
#npm run dev -- --host
npm run build
npm run preview