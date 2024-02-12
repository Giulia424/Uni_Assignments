/* Implement this class. */

import java.util.List;

public class MyDispatcher extends Dispatcher {
    public int lastHost = -1;
    public int shortestQueueHost = 0;
    public int leastWorkHost = 0;


    public MyDispatcher(SchedulingAlgorithm algorithm, List<Host> hosts) {
        super(algorithm, hosts);
    }

    @Override
    public void addTask(Task task) {
        synchronized (this) {
            if (algorithm == SchedulingAlgorithm.ROUND_ROBIN) {

                hosts.get((lastHost + 1) % hosts.size()).addTask(task);
                lastHost = (lastHost + 1) % hosts.size();
            } else if (algorithm == SchedulingAlgorithm.SHORTEST_QUEUE) {
                shortestQueueHost = 0;
                for (int i = 0; i < hosts.size(); i++)
                    if (hosts.get(i).getQueueSize() < hosts.get(shortestQueueHost).getQueueSize())
                        shortestQueueHost = i;
                hosts.get(shortestQueueHost).addTask(task);
            } else if (algorithm == SchedulingAlgorithm.SIZE_INTERVAL_TASK_ASSIGNMENT) {
                if (task.getType() == TaskType.SHORT)
                    hosts.get(0).addTask(task);
                else if (task.getType() == TaskType.MEDIUM)
                    hosts.get(1).addTask(task);
                else if (task.getType() == TaskType.LONG)
                    hosts.get(2).addTask(task);

            } else if (algorithm == SchedulingAlgorithm.LEAST_WORK_LEFT) {
                leastWorkHost = 0;
                for (int i = 0; i < hosts.size(); i++) {
                    if (hosts.get(i).getWorkLeft() < hosts.get(leastWorkHost).getWorkLeft())
                        leastWorkHost = i;
                }
                hosts.get(leastWorkHost).addTask(task);
            }
        }
    }
}