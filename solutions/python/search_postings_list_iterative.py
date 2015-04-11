# Search_postings_list_iterative.cpp b4b3a70d8ab942579f85b4416f980d05831af969
class ListNode:
    def __init__(self, order, next_node, jump):
        self.order = order
        self.next = next_node
        self.jump = jump


# @include
def search_postings_list(L):
    s = []
    order = 0
    s.append(L)
    while s:
        curr = s.pop()
        if curr and curr.order == -1:
            curr.order = order
            order += 1
            s.append(curr.next)
            s.append(curr.jump)
# @exclude


def main():
    L = curr = None
    # Build a linked list L->1->2->3->4->5->None.
    for i in range(5):
        temp = ListNode(-1, None, None)
        if curr:
            curr.next = temp
            curr = temp
        else:
            curr = L = temp

    L.jump = None                   # no jump from 1
    L.next.jump = L.next.next.next  # 2's jump points to 4
    L.next.next.jump = L            # 3's jump points to 1
    L.next.next.next.jump = None    # no jump from 4
    L.next.next.next.next.jump = L.next.next.next.next  # 5's jump points to 5
    temp = L
    search_postings_list(L)
    # output the jump-first order, should be 0, 1, 4, 2, 3
    assert temp.order == 0
    temp = temp.next
    assert temp.order == 1
    temp = temp.next
    assert temp.order == 4
    temp = temp.next
    assert temp.order == 2
    temp = temp.next
    assert temp.order == 3


if __name__ == '__main__':
    main()