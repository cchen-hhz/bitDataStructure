void inverse(LinkList head)
{
	NODE*prev=NULL;
	NODE*curr=head->next;
	NODE*next;
	while(curr!=NULL){
		next=curr->next;
		curr->next=prev;
		prev=curr;
		curr=next;
	}
	head->next=prev;
}