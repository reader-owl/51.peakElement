#include <iostream>

/*
                Q. find peak element

            explanation -  we have to find the element which is greater than its previous and next element
                                    arr[i-1] < arr[i] < arr[i+1]


                            arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 5, 1}      ans = 8     bcz 7 < 8 > 5

                            arr[] = {1, 2, 1, 3, 5, 6, 4}       ans = 2, 6      bcz 1 < 2 > 1  and 5 < 6 > 4
                            
                            arr[] = {1, 2, 3, 4, 5}     ans = 5     bcz in this case take the array as " -∞  {1, 2, 3, 4, 5}  -∞"

                            arr[] = {5, 4, 2, 3, 1}     ans = 5     bcz same as above   (taing array between "-∞ & -∞")


        Brute force -  we can search linearly, we take an element and check its previous and next element

                        lets take element 1 from index '0', left element is "-∞" which is smaller than 1, but right element 2 is greater than 1
                        lets take element 2 from index '1', left element is 1 which is smaller than 2, but right element 3 is greater than 2
                        we do the same process till element 7
                        then lets take element 8 from index '7', left element is 7 which is smaller than 8, and right element 5 is also smaller than 8

                    so 8 is peak element

        pseudo code
for(i=0; i<n; i++)
{
    if((i == 0 || arr[i-1] < arr[i]) && ((i == n-1) || arr[i] > arr[i+1]))
        return i;
}


        TC - O(N)
        SC - O(1)



            Optimized Sol -  we will be using binary search
                             if we look at the array, we can observe that some portion of it has sorted tendency

                            firstly we will assume that the array has only one peak
                            then we will expand out logic and solve with multiple peak

                    note- if the array has only one element then that element is the peak element

                    lets take example  arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 5, 1}          ans = 8
                            here we have only one peak, in this case we can have 3 conditions for peak
                    that is     1. peak is in the right of mid
                                2. peak is in the left of mid
                                3. peak is in the place of mid


                        from array low = 0, high = 9 then mid = (0+9)/2 = 4 (element 5) here we will check if the 
                        element 5 is peak or not and 5 is not the peak                                           //arr[4-1] < arr[4] > arr[4+1]
                        we can say that the peak will be at right half bcz some part of the array is sorted
                        again by binary search, low = 5, high = 9 then mid = (5+9)/2 = 7 (element 8) here we will check if the 
                        element 5 is peak or not and 8 is the peak                                           //arr[7-1] < arr[7] > arr[7+1]
                            so we will return the element 8


                    lets take another example with one peak
                                        arr[] = {1, 10, 13, 7, 6, 5, 4, 2, 1, 0}    ans = 8
                        here low = 0, high = 9 then  mid = (0+9)/2 = 4 (element 6) here we will check if the 
                        element 6 is peak or not and 6 is not the peak                                           //arr[4-1] < arr[4] > arr[4+1]
                        we can say that the peak will be at left half bcz some part of the array is sorted
                        again by binary search, low = 0, high = 3 then mid = (0+3)/2 = 1 (element 10) here we will check if the 
                        element 10 is peak or not and 10 is not the peak                                           //arr[1-1] < arr[1] > arr[1+1]
                        we can say that the peak will be at right half bcz some part of the array is sorted
                        again by binary search, low = 2, high = 3 then mid = (2+3)/2 = 2 (element 13) here we will check if the 
                        element 13 is peak or not and 13 is the peak                                           //arr[2-1] < arr[2] > arr[2+1]
                            so we will return the element 13


                    what happens if first element is the peak or the last element is the peak
                            for exa -  take array - arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
                                    here element 10 is the peak bcz it is greater than 9 and also greater than "-∞"

                         another exa -  take array - arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}
                                    here element 10 is the peak bcz it is greater than "-∞" and also greater than 9

                    to solve this two scenarios we have to check for index '0' and index 'n-1'
                                i.e,    arr[0] > arr[1]  and  arr[n-1] > arr[n-2]
                                        we have to check the above conditions separately
                    after that we will binary search from index '1' to 'n-2' 

        pseudo code (for single peak)
f(arr, n)
{
    if(n==1)
        return 0;

    if(arr[0] > arr[1])
        return 0;

    if(arr[n-1] > arr[n-2])
        return n-1;

    low = 1, high = n-2;
    while(low <= high)
    {
        mid = (low + high)/2
        if(arr[mid] > arr[mid - 1]  && arr[mid] > arr[mid + 1])
            return mid;
        else if(arr[mid] > arr[mid - 1])
            low = mid + 1;
        else if(arr[mid] > arr[mid + 1])
            high = mid - 1;
    }
    return -1;
}


        pseudo code (for multiple peak)
f(arr, n)
{
    if(n==1)
        return 0;

    if(arr[0] > arr[1])
        return 0;

    if(arr[n-1] > arr[n-2])
        return n-1;

    low = 1, high = n-2;
    while(low <= high)
    {
        mid = (low + high)/2
        if(arr[mid] > arr[mid - 1]  && arr[mid] > arr[mid + 1])
            return mid;
        else if(arr[mid] > arr[mid - 1])
            low = mid + 1;
        else if(arr[mid] > arr[mid + 1])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}


        Actual code
int findPeakElement(vector<int> &arr)
{
    int n = arr.size();
    if(n == 1)
        return 0;
    if(arr[0] > arr[1])
        return 0;
    if(arr[n-1] > arr[n-2])
        return n-1;

    int low = 0, high = n-2;
    while(low <= high)
    {
        int mid = (low + high) / 2;
        if(arr[mid] > arr[mid - 1]  && arr[mid] > arr[mid + 1])
            return mid;
        else if(arr[mid] > arr[mid - 1])
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}


            TC - O(log base2 N)
*/

int main()
{
    std::cout << "Hello World!\n";
}