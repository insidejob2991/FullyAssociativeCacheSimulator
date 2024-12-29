# Fully Associative Cache Simulator

This project is a detailed simulator for fully associative caches, designed to emulate real-world cache behavior. The simulator calculates tag bits, byte offsets, and indexes to evaluate cache hits and misses. It employs the Least Recently Used (LRU) algorithm to manage cache replacements efficiently.

## Features

- **Cache Operations**: Simulates cache hits and misses based on input memory traces.
- **LRU Replacement Policy**: Efficiently replaces the least recently used cache block to optimize performance.
- **Customizations**:
  - Varying cache sizes (e.g., 128KB to 4096KB)
  - Varying block sizes (e.g., 1 byte to 128 bytes)
  - Varying levels of associativity (e.g., 1-way to 64-way)

## How It Works

1. **Memory Address Parsing**: Divides memory addresses into tag bits, index bits, and byte offsets.
2. **Cache Hit/Miss Calculation**: Determines whether a memory access results in a cache hit or miss.
3. **Dynamic Configuration**: Allows users to experiment with different cache configurations:
   - **Cache Size**: Larger sizes reduce miss rates but show diminishing returns.
   - **Block Size**: Balances spatial locality and cache pollution.
   - **Associativity**: Increases hit rates by reducing conflict misses.

## Graphical Insights

- **Miss Rate vs. Cache Size**: Illustrates the impact of cache size on miss rates.
- **Miss Rate vs. Block Size**: Demonstrates how block size influences spatial locality and cache pollution.
- **Hit Rate vs. Associativity**: Shows the effect of associativity on conflict misses.

## Requirements

- Python 3.x
- Matplotlib (for graphing results)

## Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/FullyAssociativeCacheSimulator.git
   cd FullyAssociativeCacheSimulator
