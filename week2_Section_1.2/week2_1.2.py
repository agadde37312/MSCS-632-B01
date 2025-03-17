var1 = "Global variable"

def outer_function():
    var2 = "I'm in outside function"

    def inner_function():
        var3 = "I'm in inside function"
        print(var3)  # Accessible here
        print(var2)  # Accessible due to closure
        print(var1) # Accessible (global scope)

    inner_function()
    #print(var3)  # Error: var3 is not accessible here

#print(var2) # Error: var2 is not accessible here
outer_function()