class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        string digits = "123456789";
        vector<int> ans;

        int lowLen = to_string(low).size();
        int highLen = to_string(high).size();

        for (int len = lowLen; len <= highLen; len++) {

            for (int start = 0; start + len <= 9; start++) {

                int num = stoi(digits.substr(start, len));

                if (num >= low && num <= high) {
                    ans.push_back(num);
                }
            }
        }

        return ans;
    }
};