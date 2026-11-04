## Disclaimer: Do not share outside of this class. I will probably make this repo private after this semester

At the end of the day, I do not have a perfect guage of what Prof Sriram and
Eldon will set for your PE. They may choose to or not choose to test anything
covered by last year's PE and practices. The most reliable practices you can
do are any volumes provided during this semester. Instead of doing any of the
leetcode/past year practices, consider redoing this year's volumes (especially
the later ones) instead.

# PE2 Practice

#### TLDR: If you only have limited practice time, jump straight to the Trees section

#### Warning: The practices provided in this repository are not in c23. `<stdbool.h>` is not included by default and there are no `nullptr`

Based on the last few topics taught, string handling, linked list and trees seem
to be the hardest topics they can test. Additionally, they will likely test the use of
globals and statics. This repository consist of practices
targeted towards these 3 topics. I have included the AY2526 PE3 (the equivalent
of your PE2) paper if you want to try it under timed conditions, but it mostly
consists of string based questions. They will likely test a 1 mark question on
input handling. You should consider copying a few input handling options into
your cheatsheet. PE3 and parse-formula come with input handling practice.

By now, you should know how to pull from a remote Git repository. If you
missed this week's tutorial, refer to the tutorial sheet [here](https://cs1010.org/tutorials/tut-10-git).

## String handling

You may consider if it is worth using the <string.h> library to handle your string
inputs. The pro being that it could save you a lot of time, and the con being
unfamiliarity with the specifics could make debugging difficult. I will leave a
reference to a [resource](https://www.w3schools.com/c/c_ref_string.php)
if you would like to take a look, as well as my personal recommendations below.

| function | description | usage |
| -------- | ----------- | ----- |
| `strdup`/`strndup` | returns a copy of given string into a malloced array with a null terminator | `char *base = strdup(".")` |
| `strchr`/`strstr` | returns a pointer to the first occurance of a character/substring within a given string. returns NULL otherwise | `char *ptr = strchr(str, ' ')` |
| `strcmp`/`strncmp` | compares 2 strings. returns 0 if same, returns negative if s1 < s2, returns positive if s1 > s2 | `if (strcmp(s1, s2) == 0)` |

### Practices

- You can treat the PE3 and parse-formula practice given as string practice
- (Remind me to update) Word Mash from lab 10

## Linked List

Between linked list and trees, they are likely to test for trees more often, but
it's still good to have some linked list practice nonetheless. Linked lists
are best solved using common utility:

- Finding the index of a node
- Finding the length of a linked list
- Removing a node from a linked list given its index
- Removing a node from a linked list given its address
- Printing a linked list
- freeing a linked list

### Practices

- [Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/description/)
- [Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/description/)
- [Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/)
- If you still need more practice, go to [leetcode](https://leetcode.com/problemset/) and under topics, filter for linked list
- Additionally, if you didn't give [Scheduler](https://cs1010.org/exercise-volumes/volume-8#2-scheduler)
a proper attempt, redo the question and aim for the cleanest possible solution.
Write as many linked list helper functions as you can. These functions are
the best possible practice you can get for linked lists

## Trees

Trees are almost certainly going to be tested. Unfortunately leetcode's trees
are mostly binary trees, while yours are more similar to the one in mkdir.
Fortunately, the profs have not left you hanging. Of all the practices
you should attempt, this is the one.

Not all Trees are the same, but most Trees are best traversed with a mix of
iteration and recursion. Common tree utility include:

- Finding the next node to recurse into
- Finding if a node exists within the current tree
- Printing a tree
- Freeing a tree

### Practices

- [Volume Trees Practice](https://cs1010.org/exercise-volumes/tree-practice): You
may approach any one of your tutors if you get stuck,
but the struggle is the point of the practice.
- (Remind me to update) Delivery Truck from lab 10
- I have provided routing as tree practice as well.
- If you have not given [mkdir](https://cs1010.org/exercise-volumes/volume-8#3-mkdir)
a shot without AI which I suspect is a large number of you,
please give it another shot. Take a quick look at the solution,
understand it, then from a blank slate try again. mkdir utilizes many common tree
traversal paradigms that will make solving it much easier.
Work on those first, then use those to solve the bigger question.

## Globals and statics

Unfortunately, leetcode also has no globals or statics practice. Luckily,
lab 10 has provided 1 and it is a doozy.

### Practices

- (Remind me to update) Allocators in lab 10.
