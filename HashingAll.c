/*
 * Dynamic Hash Table Implementation in C
 * 
 * Features:
 * - Dynamic resizing (grows and shrinks as needed)
 * - Multiple hash functions
 * - Support for different collision resolution strategies
 * - Comprehensive helper functions
 * - Support for different key/value types
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 #include <stdint.h>
 #include <math.h>
 #include <time.h>
 
 /* Hash table entry states */
 typedef enum {
     EMPTY = 0,
     OCCUPIED = 1, 
     DELETED = 2
 } EntryState;
 
 /* Collision resolution strategy */
 typedef enum {
     LINEAR_PROBING = 0,
     QUADRATIC_PROBING = 1,
     DOUBLE_HASHING = 2
 } CollisionStrategy;
 
 /* Hash function type */
 typedef enum {
     HASH_FUNCTION_DIVISION = 0,
     HASH_FUNCTION_MULTIPLICATION = 1,
     HASH_FUNCTION_JENKINS = 2,
     HASH_FUNCTION_FNV = 3
 } HashFunctionType;
 
 /* Hash table entry */
 typedef struct {
     void* key;
     void* value;
     size_t key_size;
     size_t value_size;
     EntryState state;
 } HashEntry;
 
 /* Hash table */
 typedef struct {
     HashEntry* entries;
     size_t capacity;
     size_t size;
     size_t deleted_count;
     float load_factor_threshold;
     float shrink_threshold;
     CollisionStrategy collision_strategy;
     HashFunctionType hash_function_type;
     
     /* Function pointers for custom key operations */
     uint32_t (*hash_func)(const void* key, size_t key_size, size_t capacity);
     bool (*key_compare)(const void* key1, const void* key2, size_t key_size);
 } HashTable;
 
 /* Function prototypes */
 HashTable* hash_table_create(size_t initial_capacity, float load_factor_threshold, 
                            float shrink_threshold, CollisionStrategy collision_strategy,
                            HashFunctionType hash_function_type);
 void hash_table_destroy(HashTable* table);
 bool hash_table_insert(HashTable* table, const void* key, size_t key_size, 
                      const void* value, size_t value_size);
 bool hash_table_get(const HashTable* table, const void* key, size_t key_size, 
                   void* value_out, size_t value_size);
 bool hash_table_remove(HashTable* table, const void* key, size_t key_size);
 void hash_table_clear(HashTable* table);
 bool hash_table_contains(const HashTable* table, const void* key, size_t key_size);
 size_t hash_table_size(const HashTable* table);
 bool hash_table_is_empty(const HashTable* table);
 float hash_table_load_factor(const HashTable* table);
 void hash_table_print(const HashTable* table, void (*print_key)(const void*), 
                     void (*print_value)(const void*));
 void hash_table_rehash(HashTable* table, size_t new_capacity);
 void hash_table_set_hash_function(HashTable* table, 
                                 uint32_t (*hash_func)(const void*, size_t, size_t));
 void hash_table_set_key_compare(HashTable* table, 
                               bool (*key_compare)(const void*, const void*, size_t));
 void* hash_table_keys(const HashTable* table, size_t key_size, size_t* out_count);
 void* hash_table_values(const HashTable* table, size_t value_size, size_t* out_count);
 void hash_table_foreach(const HashTable* table, void (*func)(const void* key, const void* value));
 HashTable* hash_table_copy(const HashTable* table);
 bool hash_table_equals(const HashTable* table1, const HashTable* table2, 
                      bool (*value_equals)(const void*, const void*, size_t));
 void hash_table_stats(const HashTable* table);
 
 /* Hash functions */
 uint32_t hash_division(const void* key, size_t key_size, size_t capacity);
 uint32_t hash_multiplication(const void* key, size_t key_size, size_t capacity);
 uint32_t hash_jenkins(const void* key, size_t key_size, size_t capacity);
 uint32_t hash_fnv(const void* key, size_t key_size, size_t capacity);
 uint32_t hash_string(const char* str, size_t capacity);
 uint32_t hash_int(int key, size_t capacity);
 uint32_t hash_double(double key, size_t capacity);
 uint32_t hash_student(const void* key, size_t key_size, size_t capacity);
 
 /* Default key comparison function */
 bool default_key_compare(const void* key1, const void* key2, size_t key_size);
 bool compare_student(const void* key1, const void* key2, size_t key_size);
 
 /* Helper functions */
 bool is_prime(size_t n);
 size_t next_prime(size_t n);
 size_t string_key_size(const char* str);
 void* allocate_and_copy(const void* src, size_t size);
 void print_int_key(const void* key);
 void print_string_key(const void* key);
 void print_int_value(const void* value);
 void print_string_value(const void* value);
 void print_student_key(const void* key);
 void print_grade_value(const void* value);
 bool value_equals_int(const void* value1, const void* value2, size_t size);
 bool value_equals_string(const void* value1, const void* value2, size_t size);
 bool value_equals_bytes(const void* value1, const void* value2, size_t size);

/* Example and benchmark functions */
void hash_table_example();
void string_to_string_example();
void custom_struct_example();
void benchmark_collision_strategies();

/* Constants */
const float DEFAULT_LOAD_FACTOR = 0.75f;
const float DEFAULT_SHRINK_THRESHOLD = 0.25f;
const size_t DEFAULT_INITIAL_CAPACITY = 17; /* A prime number */
#define RESIZE_SCALE_FACTOR 2
#define FNV_PRIME 16777619
#define FNV_OFFSET_BASIS 2166136261
#define RUN_BENCHMARK 0  /* Set to 1 to run the benchmark */
 
 /*
  * Create a new hash table with the specified initial capacity and thresholds
  */
 HashTable* hash_table_create(size_t initial_capacity, float load_factor_threshold,
                            float shrink_threshold, CollisionStrategy collision_strategy,
                            HashFunctionType hash_function_type) {
     if (initial_capacity == 0) {
         initial_capacity = DEFAULT_INITIAL_CAPACITY;
     } else {
         initial_capacity = next_prime(initial_capacity);
     }
     
     if (load_factor_threshold <= 0.0f || load_factor_threshold >= 1.0f) {
         load_factor_threshold = DEFAULT_LOAD_FACTOR;
     }
     
     if (shrink_threshold <= 0.0f || shrink_threshold >= load_factor_threshold) {
         shrink_threshold = DEFAULT_SHRINK_THRESHOLD;
     }
     
     HashTable* table = (HashTable*)malloc(sizeof(HashTable));
     if (!table) {
         return NULL;
     }
     
     table->entries = (HashEntry*)calloc(initial_capacity, sizeof(HashEntry));
     if (!table->entries) {
         free(table);
         return NULL;
     }
     
     table->capacity = initial_capacity;
     table->size = 0;
     table->deleted_count = 0;
     table->load_factor_threshold = load_factor_threshold;
     table->shrink_threshold = shrink_threshold;
     table->collision_strategy = collision_strategy;
     table->hash_function_type = hash_function_type;
     table->key_compare = default_key_compare;
     
     /* Set the hash function based on type */
     switch (hash_function_type) {
         case HASH_FUNCTION_DIVISION:
             table->hash_func = hash_division;
             break;
         case HASH_FUNCTION_MULTIPLICATION:
             table->hash_func = hash_multiplication;
             break;
         case HASH_FUNCTION_JENKINS:
             table->hash_func = hash_jenkins;
             break;
         case HASH_FUNCTION_FNV:
             table->hash_func = hash_fnv;
             break;
         default:
             table->hash_func = hash_division;
     }
     
     return table;
 }
 
 /*
  * Destroy a hash table and free all associated memory
  */
 void hash_table_destroy(HashTable* table) {
     if (!table) {
         return;
     }
     
     /* Free all keys and values */
     for (size_t i = 0; i < table->capacity; i++) {
         if (table->entries[i].state == OCCUPIED) {
             free(table->entries[i].key);
             free(table->entries[i].value);
         }
     }
     
     free(table->entries);
     free(table);
 }
 
 /*
  * Find an index in the hash table for a given key
  * Returns the index where the key is found, or the first available slot
  * Sets the out_found parameter to true if the key was found
  */
 static size_t find_entry_index(const HashTable* table, const void* key, size_t key_size, bool* out_found) {
     if (!table || !key || table->capacity == 0) {
         if (out_found) *out_found = false;
         return 0;
     }
     
     uint32_t primary_hash = table->hash_func(key, key_size, table->capacity);
     uint32_t hash_value = primary_hash % table->capacity;
     uint32_t secondary_hash = 0;
     
     if (table->collision_strategy == DOUBLE_HASHING) {
         /* Ensure secondary hash is non-zero and relatively prime to table size 
          * This is essential for double hashing to guarantee that all slots will
          * eventually be probed if the table size is prime
          */
         secondary_hash = 1 + (primary_hash % (table->capacity - 1));
     }
     
     size_t deleted_index = table->capacity; /* Remember the first deleted spot */
     size_t i = 0;
     
     while (i < table->capacity) {
         size_t index;
         
         /* Different probing strategies:
          * LINEAR_PROBING: Simple and cache-friendly, but suffers from primary clustering
          *                 probe(i) = (hash_value + i) % capacity
          * 
          * QUADRATIC_PROBING: Reduces clustering, but may not probe all slots if capacity is not prime
          *                    probe(i) = (hash_value + i^2) % capacity
          * 
          * DOUBLE_HASHING: Best distribution, avoids clustering by using a second hash function
          *                 probe(i) = (hash_value + i * secondary_hash) % capacity
          */
         switch (table->collision_strategy) {
             case LINEAR_PROBING:
                 index = (hash_value + i) % table->capacity;
                 break;
             case QUADRATIC_PROBING:
                 index = (hash_value + (i * i)) % table->capacity;
                 break;
             case DOUBLE_HASHING:
                 index = (hash_value + (i * secondary_hash)) % table->capacity;
                 break;
             default:
                 index = (hash_value + i) % table->capacity;
         }
         
         if (table->entries[index].state == EMPTY) {
             /* Found an empty spot, key is not in the table */
             if (out_found) *out_found = false;
             /* If we found a deleted entry before, return that one instead */
             return (deleted_index < table->capacity) ? deleted_index : index;
         }
         
         if (table->entries[index].state == DELETED) {
             /* Remember the first deleted spot we find */
             if (deleted_index == table->capacity) {
                 deleted_index = index;
             }
         } else if (table->entries[index].key_size == key_size &&
                    table->key_compare(table->entries[index].key, key, key_size)) {
             /* Found the key */
             if (out_found) *out_found = true;
             return index;
         }
         
         i++;
     }
     
     /* Table is full and key was not found */
     if (out_found) *out_found = false;
     return (deleted_index < table->capacity) ? deleted_index : 0;
 }
 
 /*
  * Resize the hash table to the new capacity
  */
 void hash_table_rehash(HashTable* table, size_t new_capacity) {
     if (!table || new_capacity < table->size) {
         return;
     }
     
     /* Make sure the new capacity is prime */
     new_capacity = next_prime(new_capacity);
     
     /* Create a new array of entries */
     HashEntry* new_entries = (HashEntry*)calloc(new_capacity, sizeof(HashEntry));
     if (!new_entries) {
         return;
     }
     
     /* Keep the old entries */
     HashEntry* old_entries = table->entries;
     size_t old_capacity = table->capacity;
     
     /* Update table with new array */
     table->entries = new_entries;
     table->capacity = new_capacity;
     table->size = 0;
     table->deleted_count = 0;
     
     /* Reinsert all existing entries */
     for (size_t i = 0; i < old_capacity; i++) {
         if (old_entries[i].state == OCCUPIED) {
             hash_table_insert(table, old_entries[i].key, old_entries[i].key_size, 
                             old_entries[i].value, old_entries[i].value_size);
             
             /* Free the old copy */
             free(old_entries[i].key);
             free(old_entries[i].value);
         }
     }
     
     /* Free the old array */
     free(old_entries);
 }
 
 /*
  * Insert a key-value pair into the hash table
  * Returns true on success, false on failure
  * Replaces the value if the key already exists
  */
 bool hash_table_insert(HashTable* table, const void* key, size_t key_size, 
                      const void* value, size_t value_size) {
     if (!table || !key || !value) {
         return false;
     }
     
     /* Check if the table needs to be resized */
     float current_load = (float)(table->size + 1) / table->capacity;
     if (current_load > table->load_factor_threshold) {
         hash_table_rehash(table, table->capacity * RESIZE_SCALE_FACTOR);
     }
     
     /* Find the appropriate index for this key */
     bool found;
     size_t index = find_entry_index(table, key, key_size, &found);
     
     /* If key already exists, replace the value */
     if (found) {
         void* new_value = allocate_and_copy(value, value_size);
         if (!new_value) {
             return false;
         }
         
         free(table->entries[index].value);
         table->entries[index].value = new_value;
         table->entries[index].value_size = value_size;
         return true;
     }
     
     /* Create copies of key and value */
     void* key_copy = allocate_and_copy(key, key_size);
     void* value_copy = allocate_and_copy(value, value_size);
     
     if (!key_copy || !value_copy) {
         free(key_copy);
         free(value_copy);
         return false;
     }
     
     /* Insert the new entry */
     table->entries[index].key = key_copy;
     table->entries[index].value = value_copy;
     table->entries[index].key_size = key_size;
     table->entries[index].value_size = value_size;
     table->entries[index].state = OCCUPIED;
     
     /* Update size */
     if (table->entries[index].state == DELETED) {
         table->deleted_count--;
     }
     table->size++;
     
     return true;
 }
 
 /*
  * Retrieve a value from the hash table
  * Returns true if found, false if not
  * Copies the value to value_out if found
  */
 bool hash_table_get(const HashTable* table, const void* key, size_t key_size, 
                   void* value_out, size_t value_size) {
     if (!table || !key || !value_out) {
         return false;
     }
     
     bool found;
     size_t index = find_entry_index(table, key, key_size, &found);
     
     if (!found) {
         return false;
     }
     
     /* Copy the value if sizes match */
     if (table->entries[index].value_size == value_size) {
         memcpy(value_out, table->entries[index].value, value_size);
         return true;
     } else {
         return false; /* Value size mismatch */
     }
 }
 
 /*
  * Remove a key-value pair from the hash table
  * Returns true if the key was found and removed, false otherwise
  */
 bool hash_table_remove(HashTable* table, const void* key, size_t key_size) {
     if (!table || !key) {
         return false;
     }
     
     bool found;
     size_t index = find_entry_index(table, key, key_size, &found);
     
     if (!found) {
         return false;
     }
     
     /* Free the key and value */
     free(table->entries[index].key);
     free(table->entries[index].value);
     
     /* Mark as deleted */
     table->entries[index].state = DELETED;
     table->entries[index].key = NULL;
     table->entries[index].value = NULL;
     table->entries[index].key_size = 0;
     table->entries[index].value_size = 0;
     
     /* Update counters */
     table->size--;
     table->deleted_count++;
     
     /* Check if the table needs to be shrunk */
     float current_load = (float)table->size / table->capacity;
     if (table->capacity > DEFAULT_INITIAL_CAPACITY && 
         current_load < table->shrink_threshold) {
         hash_table_rehash(table, table->capacity / RESIZE_SCALE_FACTOR);
     }
     
     return true;
 }
 
 /*
  * Clear all entries from the hash table
  */
 void hash_table_clear(HashTable* table) {
     if (!table) {
         return;
     }
     
     /* Free all keys and values */
     for (size_t i = 0; i < table->capacity; i++) {
         if (table->entries[i].state == OCCUPIED) {
             free(table->entries[i].key);
             free(table->entries[i].value);
             table->entries[i].state = EMPTY;
             table->entries[i].key = NULL;
             table->entries[i].value = NULL;
             table->entries[i].key_size = 0;
             table->entries[i].value_size = 0;
         } else if (table->entries[i].state == DELETED) {
             table->entries[i].state = EMPTY;
         }
     }
     
     table->size = 0;
     table->deleted_count = 0;
 }
 
 /*
  * Check if the hash table contains a key
  */
 bool hash_table_contains(const HashTable* table, const void* key, size_t key_size) {
     if (!table || !key) {
         return false;
     }
     
     bool found;
     find_entry_index(table, key, key_size, &found);
     return found;
 }
 
 /*
  * Get the number of key-value pairs in the hash table
  */
 size_t hash_table_size(const HashTable* table) {
     return table ? table->size : 0;
 }
 
 /*
  * Check if the hash table is empty
  */
 bool hash_table_is_empty(const HashTable* table) {
     return table ? (table->size == 0) : true;
 }
 
 /*
  * Get the current load factor of the hash table
  */
 float hash_table_load_factor(const HashTable* table) {
     if (!table || table->capacity == 0) {
         return 0.0f;
     }
     return (float)table->size / table->capacity;
 }
 
 /*
  * Print the hash table using the provided key and value print functions
  */
 void hash_table_print(const HashTable* table, void (*print_key)(const void*), 
                     void (*print_value)(const void*)) {
     if (!table || !print_key || !print_value) {
         return;
     }
     
     printf("Hash Table (size: %zu, capacity: %zu, load factor: %.2f):\n", 
            table->size, table->capacity, hash_table_load_factor(table));
     
     for (size_t i = 0; i < table->capacity; i++) {
         if (table->entries[i].state == OCCUPIED) {
             printf("[%zu] ", i);
             print_key(table->entries[i].key);
             printf(" -> ");
             print_value(table->entries[i].value);
             printf("\n");
         }
     }
 }
 
 /*
  * Set a custom hash function for the hash table
  */
 void hash_table_set_hash_function(HashTable* table, 
                                 uint32_t (*hash_func)(const void*, size_t, size_t)) {
     if (table && hash_func) {
         table->hash_func = hash_func;
     }
 }
 
 /*
  * Set a custom key comparison function for the hash table
  */
 void hash_table_set_key_compare(HashTable* table, 
                               bool (*key_compare)(const void*, const void*, size_t)) {
     if (table && key_compare) {
         table->key_compare = key_compare;
     }
 }
 
 /*
  * Get an array of all keys in the hash table
  * Returns a newly allocated array of keys
  * The caller is responsible for freeing the returned array
  * Sets out_count to the number of keys
  */
 void* hash_table_keys(const HashTable* table, size_t key_size, size_t* out_count) {
     if (!table || !out_count || table->size == 0) {
         if (out_count) *out_count = 0;
         return NULL;
     }
     
     *out_count = table->size;
     void* keys = malloc(table->size * key_size);
     if (!keys) {
         *out_count = 0;
         return NULL;
     }
     
     size_t current = 0;
     for (size_t i = 0; i < table->capacity && current < table->size; i++) {
         if (table->entries[i].state == OCCUPIED) {
             if (table->entries[i].key_size != key_size) {
                 /* Key size mismatch - caller should ensure consistency */
                 free(keys);
                 *out_count = 0;
                 return NULL;
             }
             
             /* Copy the key to the array */
             void* dest = (char*)keys + (current * key_size);
             memcpy(dest, table->entries[i].key, key_size);
             current++;
         }
     }
     
     return keys;
 }
 
 /*
  * Get an array of all values in the hash table
  * Returns a newly allocated array of values
  * The caller is responsible for freeing the returned array
  * Sets out_count to the number of values
  */
 void* hash_table_values(const HashTable* table, size_t value_size, size_t* out_count) {
     if (!table || !out_count || table->size == 0) {
         if (out_count) *out_count = 0;
         return NULL;
     }
     
     *out_count = table->size;
     void* values = malloc(table->size * value_size);
     if (!values) {
         *out_count = 0;
         return NULL;
     }
     
     size_t current = 0;
     for (size_t i = 0; i < table->capacity && current < table->size; i++) {
         if (table->entries[i].state == OCCUPIED) {
             if (table->entries[i].value_size != value_size) {
                 /* Value size mismatch - caller should ensure consistency */
                 free(values);
                 *out_count = 0;
                 return NULL;
             }
             
             /* Copy the value to the array */
             void* dest = (char*)values + (current * value_size);
             memcpy(dest, table->entries[i].value, value_size);
             current++;
         }
     }
     
     return values;
 }
 
 /*
  * Apply a function to each key-value pair in the hash table
  */
 void hash_table_foreach(const HashTable* table, void (*func)(const void* key, const void* value)) {
     if (!table || !func) {
         return;
     }
     
     for (size_t i = 0; i < table->capacity; i++) {
         if (table->entries[i].state == OCCUPIED) {
             func(table->entries[i].key, table->entries[i].value);
         }
     }
 }
 
 /*
  * Create a copy of the hash table
  * Returns a newly allocated hash table that is a copy of the original
  * The caller is responsible for freeing the returned hash table
  */
 HashTable* hash_table_copy(const HashTable* table) {
     if (!table) {
         return NULL;
     }
     
     HashTable* copy = hash_table_create(table->capacity, table->load_factor_threshold,
                                       table->shrink_threshold, table->collision_strategy,
                                       table->hash_function_type);
     if (!copy) {
         return NULL;
     }
     
     /* Copy custom functions */
     copy->hash_func = table->hash_func;
     copy->key_compare = table->key_compare;
     
     /* Copy all entries */
     for (size_t i = 0; i < table->capacity; i++) {
         if (table->entries[i].state == OCCUPIED) {
             hash_table_insert(copy, table->entries[i].key, table->entries[i].key_size,
                             table->entries[i].value, table->entries[i].value_size);
         }
     }
     
     return copy;
 }
 
 /*
  * Compare two hash tables for equality
  * Returns true if the tables have the same keys and values, false otherwise
  * Uses the provided value comparison function
  */
 bool hash_table_equals(const HashTable* table1, const HashTable* table2,
                      bool (*value_equals)(const void*, const void*, size_t)) {
     if (!table1 || !table2 || !value_equals) {
         return false;
     }
     
     if (table1->size != table2->size) {
         return false;
     }
     
     for (size_t i = 0; i < table1->capacity; i++) {
         if (table1->entries[i].state == OCCUPIED) {
             void* key = table1->entries[i].key;
             size_t key_size = table1->entries[i].key_size;
             
             bool found;
             size_t index = find_entry_index(table2, key, key_size, &found);
             
             if (!found ||
                 table1->entries[i].value_size != table2->entries[index].value_size ||
                 !value_equals(table1->entries[i].value, table2->entries[index].value,
                             table1->entries[i].value_size)) {
                 return false;
             }
         }
     }
     
     return true;
 }
 
 /*
  * Print statistics about the hash table
  */
 void hash_table_stats(const HashTable* table) {
     if (!table) {
         return;
     }
     
     printf("Hash Table Statistics:\n");
     printf("  Size: %zu\n", table->size);
     printf("  Capacity: %zu\n", table->capacity);
     printf("  Deleted entries: %zu\n", table->deleted_count);
     printf("  Load factor: %.2f (threshold: %.2f)\n", 
            hash_table_load_factor(table), table->load_factor_threshold);
     printf("  Shrink threshold: %.2f\n", table->shrink_threshold);
     
     /* Count max probe length */
     size_t max_probe = 0;
     size_t total_probes = 0;
     size_t occupied_count = 0;
     
     for (size_t i = 0; i < table->capacity; i++) {
         if (table->entries[i].state == OCCUPIED) {
             bool found;
             uint32_t hash = table->hash_func(table->entries[i].key, 
                                            table->entries[i].key_size, table->capacity);
             size_t ideal_pos = hash % table->capacity;
             size_t actual_pos = i;
             size_t probe_length = (actual_pos >= ideal_pos) ? 
                                 (actual_pos - ideal_pos) : 
                                 (table->capacity + actual_pos - ideal_pos);
             
             if (probe_length > max_probe) {
                 max_probe = probe_length;
             }
             
             total_probes += probe_length;
             occupied_count++;
         }
     }
     
     double avg_probe = occupied_count > 0 ? (double)total_probes / occupied_count : 0;
     printf("  Maximum probe length: %zu\n", max_probe);
     printf("  Average probe length: %.2f\n", avg_probe);
     
     /* Print distribution of entries */
     size_t empty_count = table->capacity - table->size - table->deleted_count;
     printf("  Distribution: %.1f%% occupied, %.1f%% deleted, %.1f%% empty\n",
            100.0 * table->size / table->capacity,
            100.0 * table->deleted_count / table->capacity,
            100.0 * empty_count / table->capacity);
     
     /* Print collision strategy */
     printf("  Collision strategy: ");
     switch (table->collision_strategy) {
         case LINEAR_PROBING:
             printf("Linear Probing\n");
             break;
         case QUADRATIC_PROBING:
             printf("Quadratic Probing\n");
             break;
         case DOUBLE_HASHING:
             printf("Double Hashing\n");
             break;
         default:
             printf("Unknown\n");
     }
     
     /* Print hash function type */
     printf("  Hash function: ");
     switch (table->hash_function_type) {
         case HASH_FUNCTION_DIVISION:
             printf("Division Method\n");
             break;
         case HASH_FUNCTION_MULTIPLICATION:
             printf("Multiplication Method\n");
             break;
         case HASH_FUNCTION_JENKINS:
             printf("Jenkins Hash\n");
             break;
         case HASH_FUNCTION_FNV:
             printf("FNV Hash\n");
             break;
         default:
             printf("Custom\n");
     }
 }
 
 /* ----------------------------- Hash Functions ----------------------------- */
 
 /*
  * Division method hash function
  */
 uint32_t hash_division(const void* key, size_t key_size, size_t capacity) {
     if (!key || key_size == 0 || capacity == 0) {
         return 0;
     }
     
     uint32_t hash = 0;
     const unsigned char* bytes = (const unsigned char*)key;
     
     /* Sum all bytes */
     for (size_t i = 0; i < key_size; i++) {
         hash = (hash * 31) + bytes[i];
     }
     
     return hash;
 }
 
 /*
  * Multiplication method hash function
  * Using the golden ratio constant
  */
 uint32_t hash_multiplication(const void* key, size_t key_size, size_t capacity) {
     if (!key || key_size == 0 || capacity == 0) {
         return 0;
     }
     
     uint32_t hash = 0;
     const unsigned char* bytes = (const unsigned char*)key;
     
     /* XOR all bytes */
     for (size_t i = 0; i < key_size; i++) {
        hash = hash ^ ((hash << 5) + (hash >> 2) + bytes[i]);
    }
    
    /* Multiplication method uses this constant (derived from golden ratio) */
    const double A = 0.6180339887;
    double val = (double)hash * A;
    double frac = val - floor(val);  /* Fractional part */
    
    return (uint32_t)(capacity * frac);
}

/*
 * Jenkins hash function
 * A fast hash function with good distribution properties
 */
uint32_t hash_jenkins(const void* key, size_t key_size, size_t capacity) {
    if (!key || key_size == 0 || capacity == 0) {
        return 0;
    }
    
    uint32_t hash = 0;
    const unsigned char* bytes = (const unsigned char*)key;
    
    for (size_t i = 0; i < key_size; i++) {
        hash += bytes[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    
    return hash;
}

/*
 * FNV-1a hash function
 * A fast non-cryptographic hash function
 */
uint32_t hash_fnv(const void* key, size_t key_size, size_t capacity) {
    if (!key || key_size == 0 || capacity == 0) {
        return 0;
    }
    
    uint32_t hash = FNV_OFFSET_BASIS;
    const unsigned char* bytes = (const unsigned char*)key;
    
    for (size_t i = 0; i < key_size; i++) {
        hash ^= bytes[i];
        hash *= FNV_PRIME;
    }
    
    return hash;
}

/*
 * Hash function specifically for strings
 */
uint32_t hash_string(const char* str, size_t capacity) {
    if (!str || capacity == 0) {
        return 0;
    }
    
    uint32_t hash = 5381;  /* djb2 hash constant */
    int c;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  /* hash * 33 + c */
    }
    
    return hash;
}

/*
 * Hash function specifically for integers
 */
uint32_t hash_int(int key, size_t capacity) {
    /* Simple knuth multiplicative hash */
    uint32_t hash = key * 2654435761U;
    return hash;
}

/*
 * Hash function specifically for doubles
 */
uint32_t hash_double(double key, size_t capacity) {
    /* Convert to bits and hash the bits */
    uint64_t bits;
    memcpy(&bits, &key, sizeof(double));
    return hash_fnv(&bits, sizeof(bits), capacity);
}

/* ----------------------------- Helper Functions ----------------------------- */

/*
 * Default key comparison function
 * Returns true if keys are equal, false otherwise
 */
bool default_key_compare(const void* key1, const void* key2, size_t key_size) {
    if (!key1 || !key2) {
        return false;
    }
    
    return memcmp(key1, key2, key_size) == 0;
}

/*
 * Check if a number is prime
 */
bool is_prime(size_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (size_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    
    return true;
}

/*
 * Find the next prime number greater than or equal to n
 */
size_t next_prime(size_t n) {
    if (n <= 2) return 2;
    
    /* Start with the next odd number */
    size_t prime = n;
    if (prime % 2 == 0) {
        prime++;
    }
    
    /* Keep checking until we find a prime */
    while (!is_prime(prime)) {
        prime += 2;
    }
    
    return prime;
}

/*
 * Calculate the size of a string (including null terminator)
 */
size_t string_key_size(const char* str) {
    return str ? strlen(str) + 1 : 0;
}

/*
 * Allocate memory and copy data
 * Returns a pointer to the new memory or NULL on failure
 */
void* allocate_and_copy(const void* src, size_t size) {
    if (!src || size == 0) {
        return NULL;
    }
    
    void* dest = malloc(size);
    if (!dest) {
        return NULL;
    }
    
    memcpy(dest, src, size);
    return dest;
}

/*
 * Print an integer key
 */
void print_int_key(const void* key) {
    if (!key) {
        printf("(null)");
        return;
    }
    
    printf("%d", *(int*)key);
}

/*
 * Print a string key
 */
void print_string_key(const void* key) {
    if (!key) {
        printf("(null)");
        return;
    }
    
    printf("\"%s\"", (char*)key);
}

/*
 * Print an integer value
 */
void print_int_value(const void* value) {
    if (!value) {
        printf("(null)");
        return;
    }
    
    printf("%d", *(int*)value);
}

/*
 * Print a string value
 */
void print_string_value(const void* value) {
    if (!value) {
        printf("(null)");
        return;
    }
    
    printf("\"%s\"", (char*)value);
}

/*
 * Compare two integer values for equality
 */
bool value_equals_int(const void* value1, const void* value2, size_t size) {
    if (!value1 || !value2 || size != sizeof(int)) {
        return false;
    }
    
    return *(int*)value1 == *(int*)value2;
}

/*
 * Compare two string values for equality
 */
bool value_equals_string(const void* value1, const void* value2, size_t size) {
    if (!value1 || !value2) {
        return false;
    }
    
    return strcmp((char*)value1, (char*)value2) == 0;
}

/*
 * Compare two byte arrays for equality
 */
bool value_equals_bytes(const void* value1, const void* value2, size_t size) {
    if (!value1 || !value2) {
        return false;
    }
    
    return memcmp(value1, value2, size) == 0;
}

/* ----------------------------- Example Usage ----------------------------- */

/*
 * Example demonstrating use of the hash table
 */
void hash_table_example() {
    /* Create a hash table for string keys and integer values */
    HashTable* table = hash_table_create(16, DEFAULT_LOAD_FACTOR, DEFAULT_SHRINK_THRESHOLD,
                                      QUADRATIC_PROBING, HASH_FUNCTION_FNV);
    
    /* Insert some key-value pairs */
    const char* keys[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int values[] = {100, 200, 300, 400, 500};
    
    for (int i = 0; i < 5; i++) {
        char* key_copy = strdup(keys[i]);
        hash_table_insert(table, key_copy, strlen(key_copy) + 1, &values[i], sizeof(int));
        free(key_copy);  /* Safe to free after insertion since hash table makes its own copy */
    }
    
    /* Print the table */
    printf("Initial Hash Table:\n");
    hash_table_print(table, print_string_key, print_int_value);
    
    /* Look up values */
    int value;
    if (hash_table_get(table, "banana", strlen("banana") + 1, &value, sizeof(int))) {
        printf("Value for 'banana': %d\n", value);
    } else {
        printf("'banana' not found\n");
    }
    
    /* Remove an entry */
    hash_table_remove(table, "cherry", strlen("cherry") + 1);
    
    /* Print stats and updated table */
    hash_table_stats(table);
    printf("\nUpdated Hash Table after removal:\n");
    hash_table_print(table, print_string_key, print_int_value);
    
    /* Clean up */
    hash_table_destroy(table);
}

/*
 * Example using string keys and string values
 */
void string_to_string_example() {
    HashTable* table = hash_table_create(8, DEFAULT_LOAD_FACTOR, DEFAULT_SHRINK_THRESHOLD,
                                      LINEAR_PROBING, HASH_FUNCTION_JENKINS);
    
    /* Inserting country:capital pairs */
    const char* countries[] = {"USA", "Canada", "Mexico", "France", "Germany"};
    const char* capitals[] = {"Washington DC", "Ottawa", "Mexico City", "Paris", "Berlin"};
    
    for (int i = 0; i < 5; i++) {
        char* country = strdup(countries[i]);
        char* capital = strdup(capitals[i]);
        
        hash_table_insert(table, country, strlen(country) + 1, 
                        capital, strlen(capital) + 1);
        
        free(country);
        free(capital);
    }
    
    /* Print the table */
    printf("Countries and Capitals:\n");
    hash_table_print(table, print_string_key, print_string_value);
    
    /* Look up a capital */
    char capital[64];
    if (hash_table_get(table, "France", strlen("France") + 1, 
                     capital, sizeof(capital))) {
        printf("The capital of France is: %s\n", capital);
    }
    
    /* Get all keys */
    size_t count;
    char** country_list = hash_table_keys(table, sizeof(char) * 20, &count);
    
    if (country_list) {
        printf("\nList of countries (%zu):\n", count);
        for (size_t i = 0; i < count; i++) {
            printf("  %s\n", country_list[i]);
        }
        free(country_list);
    }
    
    /* Clean up */
    hash_table_destroy(table);
}

/*
 * Custom struct example
 */
typedef struct {
    int id;
    char name[32];
    float score;
} Student;

/* Custom hash function for Student struct */
uint32_t hash_student(const void* key, size_t key_size, size_t capacity) {
    const Student* student = (const Student*)key;
    uint32_t hash = hash_int(student->id, capacity);
    hash = hash ^ hash_string(student->name, capacity);
    return hash;
}

/* Custom comparison function for Student struct */
bool compare_student(const void* key1, const void* key2, size_t key_size) {
    const Student* s1 = (const Student*)key1;
    const Student* s2 = (const Student*)key2;
    
    return s1->id == s2->id && strcmp(s1->name, s2->name) == 0;
}

/* Print function for Student struct key */
void print_student_key(const void* key) {
    const Student* student = (const Student*)key;
    printf("Student{id=%d, name='%s', score=%.1f}", 
           student->id, student->name, student->score);
}

/* Print function for int value */
void print_grade_value(const void* value) {
    if (!value) {
        printf("(null)");
        return;
    }
    
    char grade = *(char*)value;
    printf("%c", grade);
}

/*
 * Example using custom struct keys
 */
void custom_struct_example() {
    HashTable* table = hash_table_create(8, DEFAULT_LOAD_FACTOR, DEFAULT_SHRINK_THRESHOLD,
                                      DOUBLE_HASHING, HASH_FUNCTION_FNV);
    
    /* Set custom hash and comparison functions */
    hash_table_set_hash_function(table, hash_student);
    hash_table_set_key_compare(table, compare_student);
    
    /* Create some students */
    Student students[] = {
        {1001, "Alice", 95.5f},
        {1002, "Bob", 82.3f},
        {1003, "Charlie", 77.8f},
        {1004, "Diana", 91.2f},
        {1005, "Ethan", 68.7f}
    };
    
    /* Assign letter grades */
    char grades[] = {'A', 'B', 'C', 'A', 'D'};
    
    /* Insert students and grades */
    for (int i = 0; i < 5; i++) {
        hash_table_insert(table, &students[i], sizeof(Student),
                        &grades[i], sizeof(char));
    }
    
    /* Print the table */
    printf("Student Grades:\n");
    hash_table_print(table, print_student_key, print_grade_value);
    
    /* Look up a grade */
    Student lookup = {1003, "Charlie", 0.0f};  /* score doesn't matter for comparison */
    char grade;
    
    if (hash_table_get(table, &lookup, sizeof(Student), &grade, sizeof(char))) {
        printf("\nCharlie's grade: %c\n", grade);
    }
    
    /* Clean up */
    hash_table_destroy(table);
}

/*
 * Main function to demonstrate the hash table
 */
int main() {
    printf("=== String to Int Example ===\n");
    hash_table_example();
    
    printf("\n=== String to String Example ===\n");
    string_to_string_example();
    
    printf("\n=== Custom Struct Example ===\n");
    custom_struct_example();
    
    /* Run the benchmark if RUN_BENCHMARK is enabled */
    #if RUN_BENCHMARK
    printf("\n");
    benchmark_collision_strategies();
    #endif
    
    return 0;
}

/*
 * Benchmark different collision resolution strategies
 * This function can be used to compare the performance of different strategies
 */
void benchmark_collision_strategies() {
    const int NUM_ITEMS = 10000;
    const int NUM_LOOKUPS = 5000;
    const int KEY_RANGE = 20000;  /* Range for generating keys - forces collisions */
    int keys[NUM_ITEMS];
    int values[NUM_ITEMS];
    clock_t start, end;
    double cpu_time_used;
    
    printf("=== Collision Resolution Strategy Benchmark ===\n");
    printf("Inserting %d items and performing %d lookups\n", NUM_ITEMS, NUM_LOOKUPS);
    
    /* Generate random data */
    srand(time(NULL));
    for (int i = 0; i < NUM_ITEMS; i++) {
        keys[i] = rand() % KEY_RANGE;
        values[i] = rand();
    }
    
    /* Test each collision strategy */
    CollisionStrategy strategies[] = {LINEAR_PROBING, QUADRATIC_PROBING, DOUBLE_HASHING};
    const char* strategy_names[] = {"Linear Probing", "Quadratic Probing", "Double Hashing"};
    
    for (int s = 0; s < 3; s++) {
        /* Create hash table with the current strategy */
        HashTable* table = hash_table_create(NUM_ITEMS / 2, DEFAULT_LOAD_FACTOR, 
                                           DEFAULT_SHRINK_THRESHOLD, 
                                           strategies[s], HASH_FUNCTION_FNV);
        
        /* Measure insertion time */
        start = clock();
        for (int i = 0; i < NUM_ITEMS; i++) {
            hash_table_insert(table, &keys[i], sizeof(int), &values[i], sizeof(int));
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        printf("\n%s:\n", strategy_names[s]);
        printf("  Insertion time: %.6f seconds\n", cpu_time_used);
        
        /* Measure lookup time - both hits and misses */
        int hits = 0;
        start = clock();
        for (int i = 0; i < NUM_LOOKUPS; i++) {
            int key = (i % 2 == 0) ? keys[i % NUM_ITEMS] : (rand() % KEY_RANGE);
            int value;
            if (hash_table_get(table, &key, sizeof(int), &value, sizeof(int))) {
                hits++;
            }
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        printf("  Lookup time: %.6f seconds (%.2f%% hit rate)\n", 
               cpu_time_used, (float)hits / NUM_LOOKUPS * 100);
        
        /* Print stats about the hash table */
        hash_table_stats(table);
        
        /* Clean up */
        hash_table_destroy(table);
    }
}