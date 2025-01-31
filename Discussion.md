# Discussion: Efficient Log Retrieval from a Large File

## Solutions Considered

### 1. **Naive Approach: Reading Line by Line**
   - **Description:**  
     In this approach, the script reads the entire log file line by line, searching for logs matching the specified date. This method is simple to implement but inefficient for large files.
   
   - **Pros:**
     - Simple and easy to implement.
   
   - **Cons:**
     - **Inefficient:** Scanning the entire file (1 TB in size) for each query can be time-consuming and resource-intensive.
     - **Memory Consumption:** Even though the file is read line by line, it requires substantial memory for temporary data storage, especially for multiple queries.
   
   - **Why not chosen:**  
     Due to its inefficiency, especially with larger files (such as 1 TB), this approach is not scalable and would be too slow for our requirements.

### 2. **Binary Search Approach**
   - **Description:**  
     The binary search approach takes advantage of the fact that the log file is already sorted by timestamp. This method involves searching for the specified date using binary search to quickly find the first log entry for that date, and then reading subsequent logs until the end of that day is reached.
   
   - **Pros:**
     - **Efficient:** Reduces the need to scan the entire file. Binary search on a sorted file can significantly speed up the process.
     - **Scalable:** Performs better for large files compared to the naive approach.
   
   - **Cons:**
     - **Complexity:** Implementing binary search requires more code and logic compared to the naive approach, although it's a one-time overhead for significant speed gains.
   
   - **Why Chosen:**  
     Since the file is already sorted, the binary search approach becomes a natural choice for this problem. It allows for very fast retrieval of the logs for a specific date, without having to read through the entire file or store unnecessary data in memory.

### 3. **Optimized Approach: Using a Hash Map with Date Indices**
   - **Description:**  
     This approach creates an index of dates, mapping each date to the starting position of its logs within the log file. The index is pre-built and stored separately, which allows the script to directly seek the logs for the given date.
   
   - **Pros:**
     - **Efficient Retrieval:** Once the date index is built, retrieving logs for any date is extremely fast.
     - **Scalable:** Suitable for large datasets because the pre-built index allows fast lookups without reading the entire file each time.
     - **Low Memory Usage:** Since only relevant logs are retrieved for the specified date, this approach minimizes memory consumption.
   
   - **Cons:**
     - **Initial Index Creation:** Building the index for a 1 TB log file can take time and require additional storage.
     - **Complexity:** The approach adds complexity in terms of maintaining and using the index, especially when logs are appended to the file.

   - **Why not chosen:**  
     Although the index approach would provide fast retrieval, the requirement to create an index for such a large file could be time-consuming and resource-heavy. Since the file is already sorted by timestamp, binary search provides a simpler and equally efficient solution.

---

## Final Solution Summary

### Approach Used
We chose the **Binary Search Approach** because:
- **Sorted Logs:** The log file is already sorted by timestamp, which makes binary search the most efficient method for quickly locating logs for a specific date.
- **Efficiency:** The binary search dramatically reduces the number of logs read, making it much faster than the naive line-by-line search method.
- **Scalability:** This solution can handle files of any size without consuming excessive memory or time, as it only reads the relevant sections of the file.

### Key Steps in the Final Solution
1. **Binary Search for Date:** Use binary search to locate the first log entry for the given date.
2. **Read Logs for the Date:** Once the start of the logs for the date is found, read and output all logs for that day.

---

## Steps to Run the Solution

1. **Clone the repository:**
   ```bash
   git clone https://github.com/SIDDHARTHA-PATWAL/tech-campus-recruitment-2025.git
   cd .\src\

## Installation Instructions for Data

To use the log file for testing, you need to download the data from the following URL:

- [Download Log Data](https://limewire.com/d/0c95044f-d489-4101-bf1a-ca48839eea86#cVKnm0pKXpN6pjsDwav4f5MNssotyy0C8Xvaor1bA5U)

Once downloaded, rename the file to `logs_2024.log` and place it in the `src` directory of the project.

