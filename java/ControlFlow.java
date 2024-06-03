public class ControlFlowExample {
    public static void main(String[] args) {
        int number = 20;

        if (number > 10) {
            System.out.println("Number is greater than 10.");
        } else {
            System.out.println("Number is 10 or less.");
        }

        for (int i = 0; i < 5; i++) {
            System.out.println("For loop iteration: " + i);
        }

        int count = 0;
        while (count < 3) {
            System.out.println("While loop iteration: " + count);
            count++;
        }

        int day = 2;
        switch (day) {
            case 1:
                System.out.println("Monday");
                break;
            case 2:
                System.out.println("Tuesday");
                break;
            default:
                System.out.println("Other day");
        }
    }
}
