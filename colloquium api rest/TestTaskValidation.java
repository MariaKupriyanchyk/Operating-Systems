package org.example;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;

import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.post;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

@WebMvcTest(TaskController.class)
class TestTaskValidation {

    @Autowired
    private MockMvc mockMvc;

    @Autowired
    private ObjectMapper objectMapper;

    @MockBean
    private TaskService taskService;

    @Test
    void TitleIsEmpty() throws Exception {
        String json = """
            {
              "title": "",
              "description": "desc",
              "status": "todo"
            }
            """;

        mockMvc.perform(post("/tasks")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(json))
                .andExpect(status().isBadRequest())
                .andExpect(jsonPath("$.title")
                        .value("Title must not be empty"));
    }

    @Test
    void TitleIsBlank() throws Exception {
        String json = """
            {
              "title": "   ",
              "description": "desc",
              "status": "todo"
            }
            """;

        mockMvc.perform(post("/tasks")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(json))
                .andExpect(status().isBadRequest())
                .andExpect(jsonPath("$.title")
                        .value("Title must not be empty"));
    }

    @Test
    void TitleTooLong() throws Exception {
        String longTitle = "a".repeat(101);

        String json = """
        {
          "title": "%s",
          "description": "desc",
          "status": "todo"
        }
        """.formatted(longTitle);

        mockMvc.perform(post("/tasks")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(json))
                .andExpect(status().isBadRequest())
                .andExpect(jsonPath("$.title")
                        .value("Title length must be at most 100 characters"));
    }

    @Test
    void DescriptionIsEmpty() throws Exception {
        String json = """
            {
              "title": "Task",
              "description": "",
              "status": "todo"
            }
            """;

        mockMvc.perform(post("/tasks")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(json))
                .andExpect(status().isBadRequest())
                .andExpect(jsonPath("$.description")
                        .value("Description must not be empty"));
    }

    @Test
    void DescriptionTooLong() throws Exception {
        String longDescription = "a".repeat(501);

        String json = """
        {
          "title": "Task",
          "description": "%s",
          "status": "todo"
        }
        """.formatted(longDescription);

        mockMvc.perform(post("/tasks")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(json))
                .andExpect(status().isBadRequest())
                .andExpect(jsonPath("$.description")
                        .value("Description must be at most 500 characters"));
    }

    @Test
    void StatusIsNull() throws Exception {
        String json = """
            {
              "title": "Task",
              "description": "desc"
            }
            """;

        mockMvc.perform(post("/tasks")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(json))
                .andExpect(status().isBadRequest())
                .andExpect(jsonPath("$.status")
                        .value("Status is required"));
    }

    @Test
    void StatusIsInvalidEnum() throws Exception {
        String json = """
            {
              "title": "Task",
              "description": "desc",
              "status": "INVALID"
            }
            """;

        mockMvc.perform(post("/tasks")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(json))
                .andExpect(status().isBadRequest())
                .andExpect(jsonPath("$.status")
                        .value("Invalid status. Allowed values: [todo, in_progress, done]"));
    }

    @Test
    void MultipleValidationErrors() throws Exception {
        String json = """
        {
          "title": "",
          "description": "",
          "status": null
        }
        """;

        mockMvc.perform(post("/tasks")
                        .contentType(MediaType.APPLICATION_JSON)
                        .content(json))
                .andExpect(status().isBadRequest())
                .andExpect(jsonPath("$.title")
                        .value("Title must not be empty"))
                .andExpect(jsonPath("$.description")
                        .value("Description must not be empty"))
                .andExpect(jsonPath("$.status")
                        .value("Status is required"));
    }
}