package org.example;

import org.springframework.cache.annotation.CacheEvict;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Service;
import org.springframework.web.server.ResponseStatusException;

import java.util.List;

@Service
public class TaskService {

    private final TaskRepository repository;

    public TaskService(TaskRepository repository) {
        this.repository = repository;
    }

    @Cacheable("tasks")
    public List<Task> getAll() {
        return repository.findAll();
    }

    @Cacheable(value = "task", key = "#id")
    public Task getById(Long id) {
        return repository.findById(id)
                .orElseThrow(() -> new ResponseStatusException(HttpStatus.NOT_FOUND,
                        "Task with id " + id + " not found"));
    }

    @CacheEvict(value = {"tasks", "task"}, allEntries = true)
    public Task create(Task task) {
        return repository.save(task);
    }

    @CacheEvict(value = {"tasks", "task"}, allEntries = true)
    public Task update(Long id, Task updated) {
        Task task = getById(id);
        task.setTitle(updated.getTitle());
        task.setDescription(updated.getDescription());
        task.setStatus(updated.getStatus());
        return repository.save(task);
    }

    @CacheEvict(value = {"tasks", "task"}, allEntries = true)
    public void delete(Long id) {
        repository.deleteById(id);
    }
}
