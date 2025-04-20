package main

import (
	"fmt"
	"log"
	"os"
	"sync"
	"time"
)

// Task represents a simple task structure
type Task struct {
	ID   int
	Data string
}

// Shared resource: results slice and mutex
var results []string
var resultMutex sync.Mutex

// Logger with timestamp and log level filtering
var (
	infoLogger  *log.Logger
	errorLogger *log.Logger
)

func initLoggers() {
	logFile, err := os.OpenFile("processing.log", os.O_CREATE|os.O_APPEND|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Printf("Failed to open log file: %v\n", err)
		os.Exit(1)
	}

	infoLogger = log.New(logFile, "INFO: ", log.Ldate|log.Ltime)
	errorLogger = log.New(logFile, "ERROR: ", log.Ldate|log.Ltime|log.Lshortfile)
}

func processTask(task Task, id int) {
	infoLogger.Printf("Worker %d started processing task %d\n", id, task.ID)

	// Simulate work with sleep
	time.Sleep(time.Millisecond * 500)

	processed := fmt.Sprintf("[%s] Worker %d processed task ID: %d - Data: %s",
		time.Now().Format(time.RFC3339), id, task.ID, task.Data)

	resultMutex.Lock()
	results = append(results, processed)
	resultMutex.Unlock()

	infoLogger.Printf("Worker %d completed task %d\n", id, task.ID)
}

func worker(id int, tasks <-chan Task, wg *sync.WaitGroup) {
	defer wg.Done()
	for task := range tasks {
		func() {
			defer func() {
				if r := recover(); r != nil {
					errorLogger.Printf("Worker %d recovered from panic: %v\n", id, r)
				}
			}()
			processTask(task, id)
		}()
	}
}

func main() {
	initLoggers()

	numWorkers := 4
	numTasks := 10

	tasks := make(chan Task, numTasks)
	var wg sync.WaitGroup

	// Start workers
	for i := 1; i <= numWorkers; i++ {
		wg.Add(1)
		go worker(i, tasks, &wg)
	}

	// Send tasks
	for i := 1; i <= numTasks; i++ {
		tasks <- Task{ID: i, Data: fmt.Sprintf("Payload_%d", i)}
	}
	close(tasks)

	// Wait for all workers to finish
	wg.Wait()

	// Display results
	fmt.Println("\n--- Processed Results ---")
	for _, result := range results {
		fmt.Println(result)
	}
}

