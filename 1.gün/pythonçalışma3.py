# Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
# The overall run time complexity should be O(log (m+n)).

def findMedianSortedArrays(nums1, nums2):
    # İki dizinin toplam uzunluğunu bul
    total_length = len(nums1) + len(nums2)
    is_even = total_length % 2 == 0
    # Ortadaki indisleri hesapla
    mid_index1 = (total_length - 1) // 2
    mid_index2 = mid_index1 + 1 if is_even else mid_index1

    # Ortadaki değerleri bulmak için işaretçi
    ptr1, ptr2 = 0, 0
    current_index = 0
    median_sum = 0

    while ptr1 < len(nums1) or ptr2 < len(nums2):
        # İşaretçi 1'in değeri varken veya İşaretçi 2'nin değeri varken devam edin
        if ptr1 < len(nums1) and (ptr2 >= len(nums2) or nums1[ptr1] <= nums2[ptr2]):
            current_num = nums1[ptr1]
            ptr1 += 1
        else:
            current_num = nums2[ptr2]
            ptr2 += 1
        # Ortanca indisleri kontrol edin
        if current_index == mid_index1 or current_index == mid_index2:
            median_sum += current_num
        current_index += 1
    # Ortanca değeri döndürün
    if is_even:
        return median_sum / 2
    else:
        return median_sum


nums1 = [1, 3]
nums2 = [2]
result = findMedianSortedArrays(nums1, nums2)
print("Ortanca Değer:", result)
