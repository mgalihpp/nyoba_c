import java.util.Arrays;
import java.util.List;

public class Streams {
    public static void main(String[] args) {
        List<String> names = Arrays.asList("John", "Jane", "Jack", "Jill");

        names.stream()
            .filter(name -> name.startsWith("J"))
            .map(String::toUpperCase)
            .forEach(System.out::println);
    }
}
