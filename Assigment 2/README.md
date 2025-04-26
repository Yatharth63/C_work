# Hash Table Implementation

This is a C implementation of a hash table with chaining collision resolution. The program demonstrates how to store and retrieve coordinate tuples efficiently using a hash table data structure.

## Features

- Hash table with chaining collision resolution
- Dynamic memory allocation for nodes
- Tuple-based coordinate storage
- Insert, search, and display operations
- Memory leak prevention with proper cleanup

## Implementation Details

### Data Structures

- `Node`: A structure containing:
  - `coordinate`: String storage for coordinate tuples (max 99 chars + null terminator)
  - `next`: Pointer to the next node in the chain

### Key Functions

1. `hash(char* str)`: 
   - Converts a coordinate tuple string to a hash value
   - Uses ASCII value summation and modulo operation
   - Returns an index between 0 and TABLE_SIZE-1

2. `insert(char* coordinate)`:
   - Inserts a new coordinate tuple into the hash table
   - Handles collisions using chaining
   - Prepends new nodes to the linked list for O(1) insertion

3. `search(char* coordinate)`:
   - Searches for a coordinate tuple in the hash table
   - Returns 1 if found, 0 if not found
   - Includes informative console output

4. `display()`:
   - Shows the contents of the hash table
   - Displays each bucket's linked list

5. `freeTable()`:
   - Properly deallocates all memory
   - Prevents memory leaks

## Usage

The main function demonstrates the usage of the hash table with example coordinate tuples:

```c
char* coordinates[] = {
    "(23.5, 45.2)", "(12.3, 78.9)", "(34.7, 56.1)", "(89.2, 12.4)", "(45.6, 67.8)"
};
```

### Compilation

```bash
gcc code_4_1_2024635.c -o hash_table
```

### Running

```bash
./hash_table
```

## Example Output

The program will:
1. Insert all coordinate tuples into the hash table
2. Display the hash table contents
3. Search for existing and non-existing coordinate tuples
4. Clean up allocated memory

## Configuration

- `TABLE_SIZE`: Can be adjusted based on expected data size (default: 10)
- Maximum coordinate tuple string length: 99 characters
- Coordinate format: "(x, y)" where x and y are numerical values

## Memory Management

- Uses dynamic memory allocation for nodes
- Includes proper cleanup to prevent memory leaks
- Safe string copying with strcpy

## Notes

- This implementation uses a simple hash function that sums ASCII values
- For production use, consider implementing a more sophisticated hash function
- The chaining approach ensures all coordinate tuples can be stored regardless of collisions
- Coordinate tuples are stored as strings in the format "(x, y)" 