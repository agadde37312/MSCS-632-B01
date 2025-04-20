import java.util.concurrent.*;
import java.util.*;
import java.io.*;
import java.util.logging.*;
import java.text.SimpleDateFormat;
import java.util.logging.Formatter;


public class DataProcessingSystem {

    private final Queue<String> taskQueue = new LinkedList<>();
    private final List<String> processedResults = Collections.synchronizedList(new ArrayList<>());
    private final ExecutorService executor;
    private final Object queueLock = new Object();
    private final int numberOfWorkers;
    private static final Logger logger = Logger.getLogger(DataProcessingSystem.class.getName());
    static class JsonFormatter extends Formatter {
        private final SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

        @Override
        public String format(LogRecord record) {
            String timestamp = sdf.format(new Date(record.getMillis()));
            String level = record.getLevel().getName();
            String message = record.getMessage().replace("\"", "\\\"");
            return String.format("{\"timestamp\":\"%s\", \"level\":\"%s\", \"message\":\"%s\"}%n",
                    timestamp, level, message);
        }
    }

    public DataProcessingSystem(int numberOfWorkers) {
        this.numberOfWorkers = numberOfWorkers;
        this.executor = Executors.newFixedThreadPool(numberOfWorkers);
        setupLogger();
    }

    private void setupLogger() {
        try {
            // Rotate after 1MB, keep up to 5 logs
            FileHandler fileHandler = new FileHandler("system.log", 1024 * 1024, 5, true);
            fileHandler.setFormatter(new JsonFormatter());
            fileHandler.setLevel(Level.INFO);

            logger.addHandler(fileHandler);
            logger.setLevel(Level.INFO);
            logger.setUseParentHandlers(true); // Also prints to console
        } catch (IOException e) {
            System.err.println("Failed to set up logger: " + e.getMessage());
        }
    }


    public void addTask(String task) {
        synchronized (queueLock) {
            taskQueue.add(task);
            logger.info("Added task to queue: " + task);
        }
    }

    private String getTask() {
        synchronized (queueLock) {
            return taskQueue.poll();
        }
    }

    private class Worker implements Runnable {
        private final int id;

        public Worker(int id) {
            this.id = id;
        }

        @Override
        public void run() {
            logger.info("Thread-" + id + " started.");
            try {
                while (true) {
                    String task = getTask();
                    if (task == null) {
                        break;
                    }

                    logger.info("Thread-" + id + " processing task: " + task);
                    Thread.sleep(1000); // Simulate processing
                    String timestamp = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
                    processedResults.add("[" + timestamp + "] Thread-" + id + " processed: " + task);

                }
                logger.info("Thread-" + id + " completed.");
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                logger.warning("Thread-" + id + " interrupted.");
            } catch (Exception e) {
                logger.severe("Thread-" + id + " encountered error: " + e.getMessage());
            }
        }
    }

    public void startProcessing() {
        logger.info("Starting task processing...");
        for (int i = 0; i < numberOfWorkers; i++) {
            executor.execute(new Worker(i));
        }
        executor.shutdown();
        try {
            if (!executor.awaitTermination(10, TimeUnit.MINUTES)) {
                logger.warning("Processing did not finish in time.");
            } else {
                logger.info("All threads completed successfully.");
            }
            saveResultsToFile("results.txt");
        } catch (InterruptedException e) {
            logger.severe("Main thread interrupted: " + e.getMessage());
        } catch (IOException e) {
            logger.severe("Failed to write results to file: " + e.getMessage());
        }
    }

    private void saveResultsToFile(String filename) throws IOException {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {
            for (String result : processedResults) {
                writer.write(result);
                writer.newLine();
            }
            logger.info("Results saved to " + filename);
        }
    }

    public static void main(String[] args) {
        DataProcessingSystem system = new DataProcessingSystem(4);

        for (int i = 1; i <= 10; i++) {
            system.addTask("Task-" + i);
        }

        system.startProcessing();
    }
}

