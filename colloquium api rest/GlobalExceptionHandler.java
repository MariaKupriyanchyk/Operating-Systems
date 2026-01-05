package org.example;

import com.fasterxml.jackson.databind.exc.InvalidFormatException;
import org.springframework.http.HttpStatus;
import org.springframework.http.converter.HttpMessageNotReadableException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestControllerAdvice;
import java.util.Arrays;
import java.util.Map;

@RestControllerAdvice
public class GlobalExceptionHandler {

    @ResponseStatus(HttpStatus.BAD_REQUEST)
    @ExceptionHandler(org.springframework.web.bind.MethodArgumentNotValidException.class)
    public Map<String, String> handleValidationErrors(
            org.springframework.web.bind.MethodArgumentNotValidException ex
    ) {
        return ex.getBindingResult()
                .getFieldErrors()
                .stream()
                .collect(
                        java.util.stream.Collectors.toMap(
                                error -> error.getField(),
                                error -> error.getDefaultMessage(),
                                (a, b) -> a
                        )
                );
    }

    @ResponseStatus(HttpStatus.BAD_REQUEST)
    @ExceptionHandler(HttpMessageNotReadableException.class)
    public Map<String, String> handleEnumErrors(
            HttpMessageNotReadableException ex
    ) {
        if (ex.getCause() instanceof InvalidFormatException ife) {
            if (ife.getTargetType().isEnum()) {
                return Map.of(
                        "status",
                        "Invalid status. Allowed values: " +
                                Arrays.toString(ife.getTargetType().getEnumConstants())
                );
            }
        }

        return Map.of("error", "Invalid request body");
    }
}