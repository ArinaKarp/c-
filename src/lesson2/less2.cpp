class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            int target_1=0;
            int target_2=1;
            for (int i = 0; i < nums.size(); i=i+2) {
                for (int j = 1; j < nums.size(); j=j+2) {

                    if (nums[i] + nums[j] == target) {
                        target_1 = i;
                        target_2 = j;
                        break;
                    }
                }
            }
             return {target_1,target_2};
        }
};
