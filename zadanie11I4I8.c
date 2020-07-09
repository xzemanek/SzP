#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOUNDARY_REACHED 1;
#define LOWL_SUCCESS 0;
#define LOWL_OK 0;
#define LOWL_FAIL 1;
#define LOWL_PROBLEM 2;

typedef struct OWN
{
	float data;
	struct OWN *next;
}OWN;

typedef struct LOWL
{
	OWN *beg;
	OWN *cur;
}LOWL;

LOWL *lowl_create_empty(void);
{
	LOWL *rtrn;
	
	rtrn=(LOWL *)malloc(sizeof(LOWL *));
	if(rtrn==NULL)
	{
		return NULL;
	}
	rtrn->beg=NULL;
	rtrn->cur=NULL;
	return rtrn;
}

char lowl_cur_step_left(LOWL *list)
{
	if(list->cur==list->beg)
	{
		return BOUNDARY_REACHED;
	}
	OWN *leftN=list->beg;
	while(leftN->next != list->cur)
	{
		leftN=leftN->next;
	}
	list->cur=leftN;
	return LOWL_SUCCESS;
}

char lowl_cur_step_right(LOWL *list)
{
	if(list->cur->next==NULL)
	{
		return BOUNDARY_REACHED;
	}
	list->cur=list->cur->next;
	return LOWL_SUCCESS;
}

OWN *lowl_insert_right(LOWL *list, float val)
{
	OWN *newN=malloc(sizeof(OWN));
	if(newN==NULL)
	{
		return NULL;
	}
	newN->data=val;
	
	if(list->beg==NULL)
	{
		list->cur=newN;
		list->beg=newN;
		list->beg->next=NULL;
		return newN;
	}
	
	if(list->cur->next==NULL)
	{
		list->cur->next=newN;
		newN->next=NULL;
		return newN;
	}
	
	OWN *rightN=list->cur->next;
	list->cur->next=newN;
	list->cur->next->next=rigthN;
	return newN;
}

OWN *lowl_insert_left(LOWL *list, float val)
{
	OWN *newN=malloc(sizeof(OWN));
	if(newN==NULL)
	{
		return NULL;
	}
	newN->data=val;
	
	if(list->beg==NULL)
	{
		list->cur=newN;
		list->beg=newN;
		list->beg->next=NULL;
		return newN;
	}
	
	if(list->cur=list->beg)
	{
		list->beg=newN;
		list->beg->next=list->cur;
		return newN;
	}
	
	OWN *auxCur=list->cur;
	list->cur=list->beg;
	
	while(list->cur->next != auxCur)
	{
		lowl_cur_step_right(list);
	}
	lowl_insert_right(list,val);
	list->cur=auxCur;
}







void lowl_print(LOWL *list)
{	
	if(list->beg==NULL)
	{
		return;
	}
		
	OWN *printer=list->beg;
	while(printer->next!=NULL)
	{
		printf("%.2f\n",printer->data);
		printer=printer->next;	
	}		
}

char lowl_delete(LOWL* list)
{
	if(list->beg==NULL)
		return LOWL_OK;
	
	if(list->beg->next==NULL)
	{
		free(list->cur);
		list->cur=NULL;
		list->beg=NULL;
		return LOWL_OK;
	} 
	
	if(list->cur==list->beg)
	{
		lowl_cur_step_right(list);
		free(list->beg);
		list->beg=list->cur;
		return LOWL_OK;	
	}
	
	if(list->cur->next==NULL)
	{
		lowl_cur_step_left(list);
		free(list->cur->next);
		list->cur->next=NULL;
		return LOWL_OK;	
	}
	
	OWN *nextNSave=list->cur->next;
	lowl_cur_step_left(list);
	free(list->cur->next);
	list->cur->next=nextNSave;
	lowl_cur_step_right(list);
}

void lowl_destroy(LOWL *list)
{
	if(list->beg==NULL)
	{
		return;
	}
	list->cur=list->beg;
	char step=LOWL_SUCCESS;
	while(list->cur!=NULL)
	{
		lowl_delete(list);
	}
	
	free(list);
	list=NULL;
}

LOWL *lowl_create_random(unsigned int size)
{
	LOWL *rtrn ;
	OWN *newN;
	unsigned int i;
	rtrn=lowl_create_empty();
	if(size != 0)
	{
        	for(i=0;i<size;i++)
        	{
        		newN = lowl_insert_right(rtrn,(float)rand());
        		if(newN == NULL)
			{
                		return NULL;
			}
        }
	}
	rtrn->cur=rtrn->beg;
	return rtrn;			
}

char lowl_interpolate_linear(LOWL *list)
{
	OWN *curSave=list->cur;
	OWN *NewNErrorCheck;
	float newV;
	
	list->cur=list->beg;
	if(list->beg->next==NULL)
	{
		return LOWL_PROBLEM;
	}
	while(list->cur->next!=NULL)
	{
		newV=(list->cur->data+list->cur->next->data)/2;
		NewNErrorCheck=lowl_insert_right(list,newV);
		if(NewNErrorCheck==NULL)
		{
			return LOWL_PROBLEM;
		}
		lowl_cur_step_right(list);
		lowl_cur_step_right(list);
	}
	list->cur=curSave;
	return LOWL_OK;
}

int main()
{
}
