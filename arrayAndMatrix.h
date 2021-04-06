#pragma once
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
//Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.
void moveZeroes(vector<int>& nums);
//You're given a matrix represented by a two-dimensional array, and two positive integers r and c representing the row number and column 

//number of the wanted reshaped matrix, respectively.

//The reshaped matrix need to be filled with all the elements of the original matrix in the same row - traversing order as they were.

//If the 'reshape' operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original 
//matrix.
vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c);
//Given a binary array, find the maximum number of consecutive 1s in this array.
int findMaxConsecutiveOnes(vector<int>& nums);
//Write an efficient algorithm that searches for a target value in an m x n integer matrix.The matrix has the following properties :
//
//Integers in each row are sorted in ascending from left to right.
//Integers in each column are sorted in ascending from top to bottom.
bool searchMatrix(vector<vector<int>>& matrix, int target);
//378. Kth Smallest Element in a Sorted Matrix
//Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.
//Note that it is the kth smallest element in the sorted order, not the kth distinct element.
bool check(vector<vector<int>>&matrix, int mid, int k);
int kthSmallest(vector<vector<int>>& matrix, int k);
//287. Find the Duplicate Number
//Given an array of integers nums containing n + 1 integers where each integer is in the range[1, n] inclusive.
//There is only one repeated number in nums, return this repeated number.
int findDuplicate(vector<int>& nums);
//697. Degree of an Array
//Given a non - empty array of non - negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.
//
//Your task is to find the smallest possible length of a(contiguous) subarray of nums, that has the same degree as nums.
int findShortestSubArray(vector<int>& nums);
//766. Toeplitz Matrix
//Given an m x n matrix, return true if the matrix is Toeplitz.Otherwise, return false.
//
//A matrix is Toeplitz if every diagonal from top - left to bottom - right has the same elements.
bool isToeplitzMatrix(vector<vector<int>>& matrix);
//565. Array Nesting
//A zero - indexed array A of length N contains all integers from 0 to N - 1. Find and return the longest length of set S, where S[i] = { A[i], A[A[i]], A[A[A[i]]], ... } subjected to the rule below.
//
//Suppose the first element in S starts with the selection of element A[i] of index = i, the next element in S should be A[A[i]], and then A[A[A[i]]]… By that analogy, we stop adding right before a duplicate element occurs in S.
int arrayNesting(vector<int>& a);
//769. Max Chunks To Make Sorted
//Given an array arr that is a permutation of[0, 1, ..., arr.length - 1], we split the array into some number of "chunks" (partitions), and individually sort each chunk.After concatenating them, the result equals the sorted array.
//
//What is the most number of chunks we could have made ?
int maxChunksToSorted(vector<int>& arr);
//785. Is Graph Bipartite ?
//Given an undirected graph, return true if and only if it is bipartite.
//
//Recall that a graph is bipartite if we can split its set of nodes into two independent subsets A and B, such that every edge in the graph has one node in A and another node in B.
//
//The graph is given in the following form : graph[i] is a list of indexes j for which the edge between nodes i and j exists.Each node is an integer between 0 and graph.length - 1.  
//There are no self edges or parallel edges : graph[i] does not contain i, and it doesn't contain any element twice
bool isBipartite(vector<vector<int>>& graph);

bool validColor(vector<vector<int>>&graph, vector<int>&colors, int color, int node);

vector<int> spiralOrder(vector<vector<int> > &matrix);
//给出一个有n个元素的数组S，S中是否有元素a, b, c满足a + b + c = 0？找出数组S中所有满足条件的三元组。
//注意：
//三元组（a、b、c）中的元素必须按非降序排列。（即a≤b≤c）
//解集中不能包含重复的三元组。
vector<vector<int> > threeSum(vector<int> &num);