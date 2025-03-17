struct Car {
    brand: String,
    year: u32,
}

fn create_car(brand: String, year: u32) -> Car {
    Car { brand, year } // Ownership moves to caller
}

fn main() {
    let my_car = create_car(String::from("Tesla"), 2022);
    println!("Car: {} - {}", my_car.brand, my_car.year);
} // Memory is automatically deallocated