from collections import Counter

class StatisticsCalculator:
    def __init__(self, data):
        self.data = data

    def mean(self):
        return sum(self.data) / len(self.data)

    def median(self):
        sorted_data = sorted(self.data)
        n = len(sorted_data)
        if n % 2 == 1:
            return sorted_data[n // 2]
        else:
            return (sorted_data[n // 2 - 1] + sorted_data[n // 2]) / 2

    def mode(self):
        frequency = Counter(self.data)
        most_common = frequency.most_common(1)
        return most_common[0][0] if most_common else None

def main():
    data = [1, 2, 2, 3, 4, 5, 8]
    stats = StatisticsCalculator(data)

    print(f"Mean: {stats.mean():.2f}")
    print(f"Median: {stats.median():.2f}")
    print(f"Mode: {stats.mode()}")

if __name__ == "__main__":
    main()
