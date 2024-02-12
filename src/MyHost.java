/* Implement this class. */

import java.util.*;
import java.util.concurrent.PriorityBlockingQueue;

public class MyHost extends Host {
    private PriorityBlockingQueue<Task> queue;
    private double start, end, timePassedSecs;
    long timePassedMillis, timePassedTask ;
    private Boolean running = true;
    private Task currentTask;

    public MyHost() {
        queue = new PriorityBlockingQueue<Task>(100, new Comparator<Task>() {
            @Override
            public int compare(Task o1, Task o2) {
               if(o2.getPriority()!=o1.getPriority())
                   return o2.getPriority() - o1.getPriority();
               else
                   return o1.getStart() - o2.getStart();
            }
        });
    }
    @Override
    public void run() {
        try {
            while (running) {
                currentTask = queue.poll();
                if (currentTask != null) {
                    start = Timer.getTimeDouble();
                    synchronized (this) {
                        wait(currentTask.getLeft());
                    }
                    end = Timer.getTimeDouble();
                    timePassedSecs = Math.round(end - start);
                    timePassedMillis = (long) timePassedSecs * 1000;
                    currentTask.setLeft(currentTask.getLeft() - timePassedMillis);
                    if (timePassedMillis >= currentTask.getLeft() ) {
                        currentTask.finish();
                        currentTask = null;
                    }
                }
            }
        } catch (InterruptedException e) {
        }
    }

    @Override
    public void addTask(Task task) {
        queue.add(task);
        if (currentTask != null) {
            if (currentTask.isPreemptible())
                if (task.getPriority() > currentTask.getPriority()) {
                    synchronized (this) {
                        notify();
                        queue.add(currentTask);

                    }
                }
        }
    }

    @Override
    public int getQueueSize() {

        if(currentTask!=null)
            return queue.size()+1;
        else return queue.size();
    }

    @Override
    public long getWorkLeft() {
        long workLeft = 0;
        if(currentTask != null) {
            timePassedTask = Math.round(Timer.getTimeDouble() - start) * 1000;
            workLeft += currentTask.getLeft() - timePassedTask;
        }
        for (Task task : queue)
            workLeft += task.getLeft();
        return workLeft;
    }

    @Override
    public void shutdown() {
        interrupt();
        running = false;
    }
}
