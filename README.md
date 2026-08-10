# PulseGrid

Lightweight C++ multiplayer-server prototype for real-time player simulation.

### Features
- 1,000+ simulated players with authoritative server-side state
- Spatial hash grid for near-linear proximity/collision queries
- WebSocket-ready networking interface
- Client prediction + server reconciliation model
- Redis-ready state/cache abstraction
- Docker and Kubernetes deployment examples
- 120+ parameterized test cases

## Build
```bash
cmake -S . -B build
cmake --build build
./build/pulsegrid
```

The default executable runs a deterministic 1,000-player simulation and compares spatial-grid queries with a naive scan.
