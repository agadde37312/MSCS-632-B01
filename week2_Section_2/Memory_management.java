class Car {
    String brand;
    int year;

    Car(String brand, int year) {
        this.brand = brand;
        this.year = year;
    }

    void display() {
        System.out.println("Car: " + brand + " - " + year);
    }
}

public class Main {
    public static void main(String[] args) {
        Car myCar = new Car("Toyota", 2021);
        myCar.display();

        // Java GC will clean up 'myCar' when it is no longer needed
        myCar = null;
        System.gc(); // Suggesting garbage collection (not guaranteed)
    }
}
