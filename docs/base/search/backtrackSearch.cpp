#include <iostream>
#include <vector>

using namespace std;

void backtrack(int len, int depth, vector<int> path, vector<int> selectedList, vector<int> used, vector<vector<int>> &ans)
{
    if (depth == len)
    {
        ans.push_back(path);
        return;
    }
    for (int i = 0; i < selectedList.size(); i++)
    {
        if (used[i] == 0)
        {
            int selected = selectedList[i];
            path.push_back(selected);
            used[i] = 1;

            backtrack(len, depth + 1, path, selectedList, used, ans);

            used[i] = 0;
            path.pop_back();
        }
    }
}

vector<vector<int>> permute(vector<int> &nums)
{
    vector<vector<int>> ans;
    vector<int> path;
    vector<int> used;
    for (int i = 0; i < nums.size(); i++)
    {
        used.push_back(0);
    }
    backtrack(nums.size(), 0, path, nums, used, ans);
    return ans;
}

int main()
{
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    vector<vector<int>> ans;
    ans = permute(nums);
    vector<int> temp;
    for (int i = 0; i < ans.size(); i++)
    {
        temp = ans[i];
        for (int j = 0; j < temp.size(); j++)
        {
            cout << temp[j] << " ";
        }
        cout << endl;
    }
}
