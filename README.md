# Student Database Server

Custom lightweight DBMS written in C++.

The project implements:

- custom file storage engine
- indexing subsystem
- TCP server
- query interpreter
- multithreaded request handling

---

# Features

## Storage Engine

- Binary file storage
- Fixed-size pages
- GUID-based entities
- Reuse of deleted slots

## Indexes

### Name Index
Red-Black Tree index for fast search by student name.

### Group Index
Hash-based index for searching students by group.

### Info Index
Red-Black Tree index for info field lookup.

---

# Architecture

```text
Client
   |
TCP
   |
DatabaseServer
   |
QueryInterpreter
   |
MasterStorage
   |
+-------------------+
| Storage Engine    |
| Name Index        |
| Info Index        |
| Group Index       |
+-------------------+
```

---

# Technologies

- C++17
- Boost.Asio
- STL
- Multithreading
- Custom binary serialization

---

# Build

## Requirements

- CMake
- Boost
- C++17 compiler

## Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

# Run

```bash
./StudentDatabaseServer
```

Server starts on:

```text
localhost:12345
```

---

# Example Queries

## Insert

```text
INSERT name=Ivanov;group=201;rating=4.5;info=Excellent student
```

## Select

```text
SELECT group=201
```

## Update

```text
UPDATE name=Ivanov rating=5.0
```

## Delete

```text
DELETE name=Ivanov
```

---

# Project Structure

```text
Client/      -> client application
Server/      -> database engine
build/       -> build directory
CMakeLists   -> build configuration
```

---

# Future Improvements

- WAL logging
- Transactions
- B+Tree indexes
- Persistent index storage
- Query optimizer
- Better TCP protocol

---

# Author

Educational DBMS project written in C++.
