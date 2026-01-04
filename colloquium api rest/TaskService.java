package org.example;

import org.springframework.stereotype.Service;
import java.util.List;

@Service
public class TaskService {

    private final TaskRepository repository;

    public TaskService(TaskRepository repository) {
        this.repository = repository;
    }

    public List<Task> getAll() {
        return repository.findAll();
    }

    public Task getById(Long id) {
        return repository.findById(id)
                .orElseThrow(() -> new RuntimeException("Task not found"));
    }

    public Task create(Task task) {
        return repository.save(task);
    }

    public Task update(Long id, Task updated) {
        Task existing = getById(id);
        existing.setTitle(updated.getTitle());
        existing.setDescription(updated.getDescription());
        existing.setStatus(updated.getStatus());
        return repository.save(existing);
    }

    public void delete(Long id) {
        if (!repository.exists(id)) {
            throw new RuntimeException("Task not found");
        }
        repository.delete(id);
    }
}