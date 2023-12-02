# OS-Project-2
Banker’s Algorithm for deadlock avoidance

## Introduction

A system in a safe state has no deadlocks, where a system in an unsafe state has a possibility of deadlock. The Banker's algorithm is used to define whether a system is in an unsafe or safe state, and thus can be used to avoid deadlock. For this, a process must define its maximum use of resources, it must be able to wait, and it must be able to return all its resources in a finite amount of time.
Defined in this problem will be matrices showing the maximum allocated rescoures and currently allocated resources, usually referred to as "max" and "allocated". These matrices will be n by m, n being the number of processes in the system, and m being the number of different resources. There will also be a vector of m length, simply representing how much of each resource is available.
