package org.example;

import org.springframework.stereotype.Repository;

import java.util.*;
import java.util.concurrent.atomic.AtomicLong;

@Repository
public class TaskRepository {

    private final Map<Long, Task> storage = new HashMap<>();
    private final AtomicLong idGenerator = new AtomicLong(1);

    public List<Task> findAll() {
        return new ArrayList<>(storage.values());
    }

    public Optional<Task> findById(Long id) {
        return Optional.ofNullable(storage.get(id));
    }

    public Task save(Task task) {
        if (task.getId() == null) {
            task.setId(idGenerator.getAndIncrement());
        }
        storage.put(task.getId(), task);
        return task;
    }

    public void delete(Long id) {
        storage.remove(id);
    }

    public boolean exists(Long id) {
        return storage.containsKey(id);
    }
}