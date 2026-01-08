package org.example;

import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.web.server.ResponseStatusException;
import java.util.Optional;
import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;
import org.junit.jupiter.api.extension.ExtendWith;

@ExtendWith(MockitoExtension.class)
class TestTaskService {

    @Mock
    TaskRepository repository;

    @InjectMocks
    TaskService service;

    @Test
    void getById_found() {
        Task task = new Task();
        task.setId(1L);

        when(repository.findById(1L)).thenReturn(Optional.of(task));
        Task result = service.getById(1L);

        assertEquals(1L, result.getId());
    }

    @Test
    void getById_notFound() {
        when(repository.findById(1L)).thenReturn(Optional.empty());

        assertThrows(ResponseStatusException.class,
                () -> service.getById(1L));
    }

    @Test
    void create_callsRepositorySave() {
        Task task = new Task();
        service.create(task);

        verify(repository).save(task);
    }

    @Test
    void update_updatesExistingTask() {
        Task existing = new Task();
        existing.setId(1L);
        existing.setTitle("Old");
        existing.setDescription("Old desc");
        existing.setStatus(TaskStatus.todo);

        Task updated = new Task();
        updated.setTitle("New");
        updated.setDescription("New desc");
        updated.setStatus(TaskStatus.done);

        when(repository.findById(1L)).thenReturn(Optional.of(existing));
        when(repository.save(any(Task.class))).thenAnswer(inv -> inv.getArgument(0));

        Task result = service.update(1L, updated);

        assertEquals("New", result.getTitle());
        assertEquals("New desc", result.getDescription());
        assertEquals(TaskStatus.done, result.getStatus());

        verify(repository).save(existing);
    }

    @Test
    void update_notFound_throwsException() {
        when(repository.findById(1L)).thenReturn(Optional.empty());

        assertThrows(ResponseStatusException.class,
                () -> service.update(1L, new Task()));

        verify(repository, never()).save(any());
    }

    @Test
    void delete_callsRepositoryDeleteById() {
        service.delete(1L);

        verify(repository).deleteById(1L);
    }

    @Test
    void delete_notFound_stillCallsDelete() {
        service.delete(99L);

        verify(repository).deleteById(99L);
    }
}