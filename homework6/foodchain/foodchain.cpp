#include <iostream>
#include <fstream>
class UFSets
{
private:
    int *arr;
    int size;

public:
    UFSets(int s)
    {
        this->size = s;
        arr = new int[s];
        for (int i = 0; i < s; ++i)
        {
            this->arr[i] = -1;
        }
    }
    void union_sets(int a, int b)
    {
        int r1 = find(a);
        int r2 = find(b);
        if (r1 != r2 && r1 != -1 && r2 != -1)
        {
            int temp = arr[r1] + arr[r2];
            if (arr[r1] <= arr[r2])
            {
                arr[r2] = r1;
                arr[r1] = temp;
            }
            else
            {
                arr[r1] = r2;
                arr[r2] = temp;
            }
        }
    }
    bool differ(int a, int b)
    {
        return find(a) == find(b);
    }
    int find(int e)
    {
        int i, k, p = e;
        for (i = e; arr[i] >= 0; i = arr[i])
            ;
        if (e != i)
        {
            while (i != arr[p])
            {
                k = arr[p];
                arr[p] = i;
                p = k;
            }
        }
        return i;
    }
};

/*
0---------n-1-----------2n-1-----------3n-1
    同类         猎物           天敌


*/

int main()
{
    std::ifstream input("foodchain.in");
    int n;
    int sentense_count;
    input >> n >> sentense_count;
    UFSets sets(3 * n);
    int answer = 0;
    for (int i = 0; i < sentense_count; ++i)
    {
        int k, x, y;
        input >> k >> x >> y;
        x -= 1;
        y -= 1;
        if (!(x < n && y < n))
        {
            answer += 1;
            continue;
        }

        if (k == 1)
        {
            if (sets.find(x + n) == sets.find(y) || sets.find(x + 2 * n) == sets.find(y))
            {
                answer += 1;
                continue;
            }
            sets.union_sets(x, y);
            sets.union_sets(x + n, y + n);
            sets.union_sets(x + 2 * n, y + 2 * n);
        }
        if (k == 2)
        {
            if (sets.find(x) == sets.find(y) || sets.find(x + 2 * n) == sets.find(y))
            {
                answer += 1;
                continue;
            }
            sets.union_sets(x + n, y);
            sets.union_sets(x + 2 * n, y + n);
            sets.union_sets(x, y + 2 * n);
        }
    }
    std::ofstream output("foodchain.out");
    std::cout << answer;
    output << answer;
}