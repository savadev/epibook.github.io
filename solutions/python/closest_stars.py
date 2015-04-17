# Closest_stars.cpp 07f410e6c098209e8b1ba1cc7cdd1ec09f45e485
import sys
import io
import random
import csv
import heapq


# @include
class Star:

    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    @property
    def distance(self):
        return self.x ** 2 + self.y ** 2 + self.z ** 2

    def __lt__(self, rhs):
        return self.distance < rhs.distance

    # @exclude
    def __str__(self):
        return ' '.join(map(str, (self.x, self.y, self.z)))

    def __eq__(self, rhs):
        rhs_distance = rhs.distance
        return abs(self.distance - rhs_distance) / rhs_distance < 1.0e-5
    # @include


def find_closest_k_stars(k, stars):
    # max_heap to store the closest k stars seen so far.
    max_heap = []
    reader = csv.reader(stars)
    for line in reader:
        star = Star(*map(float, line))
        # Add each star to the max-heap. If the max-heap size exceeds k,
        # remove the maximum element from the max-heap.
        # As python has only min-heap, insert tuple (negative distance, star)
        # to sort in reversed distance order
        heapq.heappush(max_heap, (-star.distance, star))
        if len(max_heap) == k + 1:
            heapq.heappop(max_heap)

    # Iteratively extract from the max-heap, which yields the stars
    # sorted according from furthest to closest.
    closest_stars = []
    while max_heap:
        closest_stars.append(heapq.heappop(max_heap)[1])

    return closest_stars
# @exclude


def main():
    for _ in range(1000):
        if len(sys.argv) == 2:
            num = int(sys.argv[1])
            k = random.randint(1, num)
        elif len(sys.argv) == 3:
            num = int(sys.argv[1])
            k = int(sys.argv[2])
        else:
            num = random.randint(1, 10000)
            k = random.randint(1, num)
        # Randomly generate num of stars.
        stars = [Star(random.uniform(0, 10000),
                      random.uniform(0, 10000),
                      random.uniform(0, 10000)) for i in range(num)]
        s = io.StringIO(newline='')
        ss = csv.writer(s)
        for star in stars:
            ss.writerow((star.x, star.y, star.z))
        s.seek(0)
        closest_stars = find_closest_k_stars(k, s)
        closest_stars.sort()
        stars.sort()
        print('k =', k)
        print(stars[k - 1])
        print(closest_stars[-1])
        assert stars[k - 1] == closest_stars[-1]


if __name__ == '__main__':
    main()
