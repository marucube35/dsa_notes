#include "Sorting.h"

void shakerSortExperiment(int a[], int n, long long &count_cmp)
{
     int left = 0;
     int right = n - 1;
     int mark = 0; // biến đánh dấu
     while (++count_cmp && left < right)
     {
          // duyệt xuôi chiều
          for (int i = left; ++count_cmp && i < right; i++)
          {
               if (++count_cmp && a[i] > a[i + 1])
               {
                    swap(a[i], a[i + 1]);
                    mark = i; // đánh dấu lại vị trí cận trên
                    // đánh dấu lại vị trí mà từ vị trí đó -> n-1 thỏa tính tăng dần
               }
          }
          right = mark;
          // duyệt ngược chiều
          for (int i = right; ++count_cmp && i > left; i--)
          {
               if (++count_cmp && a[i] < a[i - 1])
               {
                    swap(a[i], a[i - 1]);
                    mark = i; // đánh dấu lại vị trí cận dưới
                    // đánh dấu lại vị trí mà từ vị trí đó -> 0 thỏa tính giảm dần
               }
          }
          left = mark;
     }
}
