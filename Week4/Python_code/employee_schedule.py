import tkinter as tk
from tkinter import messagebox, ttk
import random

# Constants
DAYS = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday']
SHIFTS = ['Morning', 'Afternoon', 'Evening']
MAX_WORK_DAYS = 5
MIN_EMPLOYEES_PER_SHIFT = 2

# Data structures
employees = {}  # Stores employee preferences (with priority)
schedule = {day: {shift: [] for shift in SHIFTS} for day in DAYS}
workload = {}  # Tracks how many days each employee has worked

# GUI for employee scheduling
class EmployeeSchedulerApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Employee Scheduler")
        self.geometry("1000x700")
        self.create_widgets()

    def create_widgets(self):
        emp_frame = tk.LabelFrame(self, text="Manage Employees")
        emp_frame.pack(pady=10, padx=10, fill="x")

        tk.Label(emp_frame, text="Select Employee:").grid(row=0, column=0, padx=5, pady=5)
        self.employee_combobox = ttk.Combobox(emp_frame, values=list(employees.keys()), state="readonly")
        self.employee_combobox.grid(row=0, column=1)

        tk.Label(emp_frame, text="New Employee:").grid(row=0, column=2, padx=5, pady=5)
        self.new_emp_entry = tk.Entry(emp_frame)
        self.new_emp_entry.grid(row=0, column=3)

        tk.Button(emp_frame, text="Add Employee", command=self.add_new_employee).grid(row=0, column=4, padx=5)

        pref_frame = tk.LabelFrame(self, text="Shift Preferences")
        pref_frame.pack(pady=10, padx=10, fill="x")

        tk.Label(pref_frame, text="Day:").grid(row=0, column=0, padx=5, pady=5)
        self.day_combobox = ttk.Combobox(pref_frame, values=DAYS, state="readonly")
        self.day_combobox.grid(row=0, column=1)

        tk.Label(pref_frame, text="1st Preference:").grid(row=0, column=2, padx=5, pady=5)
        self.shift1_combobox = ttk.Combobox(pref_frame, values=SHIFTS, state="readonly")
        self.shift1_combobox.grid(row=0, column=3)

        tk.Label(pref_frame, text="2nd Preference:").grid(row=0, column=4, padx=5, pady=5)
        self.shift2_combobox = ttk.Combobox(pref_frame, values=SHIFTS, state="readonly")
        self.shift2_combobox.grid(row=0, column=5)

        tk.Label(pref_frame, text="3rd Preference:").grid(row=0, column=6, padx=5, pady=5)
        self.shift3_combobox = ttk.Combobox(pref_frame, values=SHIFTS, state="readonly")
        self.shift3_combobox.grid(row=0, column=7)

        tk.Button(pref_frame, text="Add Preferences", command=self.add_preference).grid(row=0, column=8, padx=5)

        button_frame = tk.Frame(self)
        button_frame.pack(pady=10)

        tk.Button(button_frame, text="Assign Shifts", command=self.assign_shifts).grid(row=0, column=0, padx=5)
        tk.Button(button_frame, text="Resolve Conflicts", command=self.resolve_conflicts).grid(row=0, column=1, padx=5)
        tk.Button(button_frame, text="Display Schedule", command=self.display_schedule).grid(row=0, column=2, padx=5)

        self.output_text = tk.Text(self, width=120, height=30)
        self.output_text.pack(pady=10)

    def add_new_employee(self):
        """Add a new employee to the system."""
        name = self.new_emp_entry.get().strip()

        if not name:
            messagebox.showerror("Error", "Please enter a valid employee name.")
            return

        if name in employees:
            messagebox.showerror("Error", "Employee already exists.")
        else:
            employees[name] = {}
            workload[name] = 0
            messagebox.showinfo("Success", f"Added new employee: {name}")
            self.employee_combobox['values'] = list(employees.keys())

        self.new_emp_entry.delete(0, tk.END)

    def add_preference(self):
        """Add shift preferences for an employee."""
        name = self.employee_combobox.get()
        day = self.day_combobox.get()
        shift1 = self.shift1_combobox.get()
        shift2 = self.shift2_combobox.get()
        shift3 = self.shift3_combobox.get()

        if not name or not day or not shift1 or not shift2 or not shift3:
            messagebox.showerror("Error", "Please fill in all preferences for shift.")
            return

        if name not in employees:
            messagebox.showerror("Error", "Employee does not exist.")
            return

        employees[name][day] = [shift1, shift2, shift3]
        messagebox.showinfo("Success", f"Added {name}'s preferences: {shift1}, {shift2}, {shift3} on {day}")

    def assign_shifts(self):
        """Assign shifts based on employee preferences while adhering to max workdays."""
        global schedule
        schedule = {day: {shift: [] for shift in SHIFTS} for day in DAYS}

        for name in employees:
            workload[name] = 0

        for name, prefs in employees.items():
            days_assigned = 0

            for day, pref_shifts in prefs.items():
                if days_assigned >= MAX_WORK_DAYS:
                    break

                # Try to assign employee based on preferences
                assigned = False
                for shift in pref_shifts:
                    if workload[name] < MAX_WORK_DAYS and len(schedule[day][shift]) < MIN_EMPLOYEES_PER_SHIFT:
                        schedule[day][shift].append(name)
                        workload[name] += 1
                        days_assigned += 1
                        assigned = True
                        break

                # If no preferred shift could be assigned, assign to any shift
                if not assigned:
                    for shift in SHIFTS:
                        if len(schedule[day][shift]) < MIN_EMPLOYEES_PER_SHIFT:
                            schedule[day][shift].append(name)
                            workload[name] += 1
                            days_assigned += 1
                            break

        messagebox.showinfo("Success", "Shifts assigned successfully!")

    def resolve_conflicts(self):
        """Ensure at least 2 employees per shift. Randomly assign 2 employees who have not worked 5 days yet."""
        for day in DAYS:
            for shift in SHIFTS:
                while len(schedule[day][shift]) < MIN_EMPLOYEES_PER_SHIFT:
                    # Get list of employees who have not worked 5 days yet
                    available = [emp for emp in employees if workload[emp] < MAX_WORK_DAYS]

                    if len(available) < 2:
                        messagebox.showerror("Error", "Not enough available employees to assign.")
                        return

                    # Randomly assign 2 employees
                    chosen_employees = random.sample(available, 2)

                    for emp in chosen_employees:
                        schedule[day][shift].append(emp)
                        workload[emp] += 1

        messagebox.showinfo("Success", "Conflicts resolved and missing employees filled!")

    def display_schedule(self):
        """Display the final schedule."""
        self.output_text.delete(1.0, tk.END)
        output = "\n===== Weekly Employee Schedule =====\n"

        for day, shifts in schedule.items():
            output += f"\n{day}\n"
            for shift, assigned in shifts.items():
                assigned_employees = ', '.join(assigned) if assigned else 'No Employees Assigned'
                output += f"  {shift}: {assigned_employees}\n"

        self.output_text.insert(tk.END, output)


if __name__ == "__main__":
    app = EmployeeSchedulerApp()
    app.mainloop()
