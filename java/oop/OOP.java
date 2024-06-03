class Dog {
    String name;
    int age;

    void bark() {
        System.out.println(name + " is barking.");
    }

    void walk(){
        System.out.println(name + " is walking.");
    }

    void eat(){
        System.out.println(name + " is eating.");
    }
}

public class OOP {
    public static void main(String[] args) {
        Dog myDog = new Dog();
        myDog.name = "Buddy";
        myDog.age = 3;
        myDog.bark();
        myDog.walk();
        myDog.eat();
    }
}
