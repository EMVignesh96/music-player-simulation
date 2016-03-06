#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct list{
	int id,no,rating;
	char name[20],genre[10],album[10];
	struct list *next;
} list;

typedef struct bstree{
	int id,rating;
	char name[20],genre[10],album[10];
	struct bstree *left;
	struct bstree *right;	
} lib;

typedef struct queue{
	char name[20],genre[10];
	struct queue *next;
} qtracks;

typedef struct stack{
	char name[20],genre[10];
	struct stack *next;
} lptracks;

qtracks *qtracksfront=NULL;
qtracks *qtracksrear=NULL;
lptracks *lptrackstop=NULL;
lib *root=NULL;

void play();
int nosongsqueued();
void nowplaying();
void queuedsongs();
void library();
void lastplayed();
void volup();
void voldown();
void mute();
void playnext();
void playprev();
qtracks* addsong(lib *, int);
void pushtolptracks(lptracks *);
lib * inserttolib(lib *,lib *);
lib * ctreenode(int,int,char *,char *,char *);
void feeddata();
void dispalb(lib *,char *);
void dispgen(lib *,char *);
int ch,ply=0,v=5,m,o;

void play(){
	if(qtracksfront==NULL){
		printf("\nCannot Play.No Songs Queued.");
		return;
	}
	ply=(ply+1)%2;
	if(ply==1)
	printf("\nThe Song is Playing...");
	if(ply==0)
	printf("\nPaused.");
}
	
void nowplaying(){
	if(qtracksfront==NULL){
		printf("\t\t\tNow Playing:----");
		return;
	}
	printf("\t\t\tNow Playing: %s",qtracksfront->name);
}

int nosongsqueued(){
	int n=0;
	qtracks *temp=qtracksfront;
	while(temp!=NULL){
		n++;
		temp=temp->next;
	}
	return n;
}

void lastplayed(){
	if(lptrackstop==NULL){
		printf("\nNo Songs Played.");
		return;
	}
	printf("\nLast Played:\nSong:%s\nGenre:%s",lptrackstop->name,lptrackstop->genre);	
}

void volup(){
	if(v==10) printf("\nYou cannot increase the Volume anymore.Hearing to this level of Loudness can cause ear problems.");
	else {
		v++;
		//printf("\nVolume level increased.\nCurrent Volume Level:%d",v);
	}
}

void voldown(){
	if(v==0) printf("\nMuted");
	else {
		v--;
		printf("\nVolume level decreased.\nCurrent Volume Level:%d",v);
	}
}

void mute(){
	//int o;
	if(v) o=v;
	m=(m+1)%2;
	if(m){
		printf("\nMuted");
		v=0;
	}
	else{
		printf("\nUnmuted");
		v=o;
	}
}

void queuedsongs(){
	qtracks *temp=qtracksfront;
	if(qtracksfront==NULL){
		printf("\nNo Songs Queued.");
		return;
	}
	printf("\nThe Queued Songs:\n");
	while(temp!=NULL){
			printf("\n\nSong:%s\nGenre:%s",temp->name,temp->genre);
			temp=temp->next;				
	}
	//printf("\n\nSong:%s\nGenre:%s",qtracksrear->name,qtracksrear->genre);
	
}

void playnext(){
	if(qtracksfront==NULL){
		printf("\nNo songs Queued.");
		return;
	}
	qtracks *temp=qtracksfront;
	lptracks *t=(lptracks *)malloc(sizeof(lptracks));
	qtracksfront=qtracksfront->next;
	strcpy(t->name,temp->name);
	strcpy(t->genre,temp->genre);
	pushtolptracks(t);
	if(qtracksfront==NULL){
		printf("\nEnd of Queue.");
		ply=0;
		return;
	}
	ply=1;
	printf("\nThe Next Song is Playing...");
}

void pushtolptracks(lptracks *t){
	if(lptrackstop==NULL){
		t->next=NULL;
		lptrackstop=t;
		return;		
	}
	t->next=lptrackstop;
	lptrackstop=t;	
}

void playprev(){
	qtracks *temp=(qtracks *)malloc(sizeof(qtracks));
	if(lptrackstop==NULL){
		printf("\nNo songs in Last Played.");
		return;
	}
	lptracks *t=lptrackstop;
	lptrackstop=lptrackstop->next;
	strcpy(temp->name,t->name);
	strcpy(temp->genre,t->genre);
	temp->next=qtracksfront;
	qtracksfront=temp;
	ply=1;
	printf("\nThe Previous Song is Playing...");
	free(t);
}

void library(){
	int c,d;
	printf("\nLibrary:\n1.Display by Album\n2.Display by Genre\nWhat do you wanna do?");
	scanf("%d",&c);
	switch(c){
		case 1: 
		printf("\n1.3\n2.Anegan\n3.Kaththi\n4.Rajarani\nWhich Album do you wanna View?");
		scanf("%d",&d);
		switch(d){
			case 1:
				dispalb(root,"3");				
				break;
			case 2:
				dispalb(root,"Anegan");				
				break;
			case 3:
				dispalb(root,"Kaththi");				
				break;
			case 4:
				dispalb(root,"Rajarani");				
				break;
		}
			break;
		case 2: 
			printf("\n1.Rock\n2.Pop\n3.Melody\n4.Gaana\nWhich Genre do you wanna listen?");
		scanf("%d",&d);
		switch(d){
			case 1:
				dispgen(root,"Rock");				
				break;
			case 2:
				dispgen(root,"Pop");				
				break;
			case 3:
				dispgen(root,"Melody");				
				break;
			case 4:
				dispgen(root,"Gaana");				
				break;
		}
			break;
	}	
}

void dispalb(lib *r,char *a){
	if(r==NULL)
	return;
		dispalb(r->left,a);
		if(!strcmp(r->album,a)){
			printf("\nSong ID: %d",r->id);
			printf("\nSong Name: %s",r->name);
			printf("\nSong Genre: %s",r->genre);
			printf("\nAlbum: %s",r->album);
			printf("\nRating: %d\n\n",r->rating);
		}
		dispalb(r->right,a);
}

void dispgen(lib *r,char *a){
	if(r==NULL)
	return;
		dispgen(r->left,a);
		if(!strcmp(r->genre,a)){
			printf("\nSong ID: %d",r->id);
			printf("\nSong Name: %s",r->name);
			printf("\nSong Genre: %s",r->genre);
			printf("\nAlbum: %s",r->album);
			printf("\nRating: %d\n\n",r->rating);
		}
		dispgen(r->right,a);
}

lib * ctreenode(int id, int rating, char *name, char *genre, char *album){
	lib *temp=(lib *)malloc(sizeof(lib));
	temp->id=id;
	temp->rating=rating;
	strcpy(temp->name,name);
	strcpy(temp->genre,genre);
	strcpy(temp->album,album);
	temp->left=temp->right=NULL;
	return temp;
}

lib * inserttolib(lib *r,lib *t){
	if(r==NULL){
		r=t;
		return r;
	}
	else if(r->id<t->id){
		r->right=inserttolib(r->right,t);
	}
	else if(r->id>t->id){
		r->left=inserttolib(r->left,t);
	}
	return r;
}

qtracks* addsong(lib *r,int id){
	if(r==NULL){
		printf("\nSong Not Found.");
		return NULL;
	}
	if(id>r->id) return addsong(r->right,id);
	
	else if(id<r->id) return addsong(r->left,id);
	
	else{
		qtracks *temp=(qtracks *)malloc(sizeof(qtracks));
		strcpy(temp->name,r->name);
		strcpy(temp->genre,r->genre);
		temp->next=NULL;
		if(qtracksfront==NULL && qtracksrear==NULL){
			qtracksfront=qtracksrear=temp;
			return temp;
		}
		qtracksrear->next=temp;
		qtracksrear=temp;	
		return temp;	
	}
}

void feeddata(){
	lib *t=ctreenode(1,4,"Why This Kolaveri","Pop","3");
	root=inserttolib(root,t);
	
	t=ctreenode(2,4,"Kannazhaga","Melody","3");
	root=inserttolib(root,t);
	
	t=ctreenode(3,3,"Idhazhin Oram","Melody","3");
	root=inserttolib(root,t);
	
	t=ctreenode(4,4,"Nee Paartha Vizhigal","Melody","3");
	root=inserttolib(root,t);
	
	t=ctreenode(5,3,"Come on Girls","Melody","3");
	root=inserttolib(root,t);
	
	t=ctreenode(6,5,"Danga Maari Oodhari","Gaana","Anegan");
	root=inserttolib(root,t);
	
	t=ctreenode(7,3,"Aathadi Aathadi","Melody","Anegan");
	root=inserttolib(root,t);
	
	t=ctreenode(8,3,"Roja Kadale","Pop","Anegan");
	root=inserttolib(root,t);
	
	t=ctreenode(9,3,"Aathadi Aathadi","Melody","Anegan");
	root=inserttolib(root,t);
	
	t=ctreenode(10,5,"Selfie Pulla","Pop","Kaththi");
	root=inserttolib(root,t);
	
	t=ctreenode(11,4,"Pakkam Vanthu","Rock","Kaththi");
	root=inserttolib(root,t);
	
	t=ctreenode(12,2,"Paalam","Gaana","Kaththi");
	root=inserttolib(root,t);
	
	t=ctreenode(13,3,"Nee Yaaro","Melody","Kaththi");
	root=inserttolib(root,t);
	
	t=ctreenode(14,5,"Aathi","Melody","Kaththi");
	root=inserttolib(root,t);
	
	t=ctreenode(15,3,"Hey Baby","Melody","Rajarani");
	root=inserttolib(root,t);
	
	t=ctreenode(16,3,"Angnyaade","Gaana","Rajarani");
	root=inserttolib(root,t);
	
	t=ctreenode(17,3,"Chillena","Rock","Rajarani");
	root=inserttolib(root,t);
	
	t=ctreenode(18,3,"Unnale","Melody","Rajarani");
	root=inserttolib(root,t);
	
	t=ctreenode(19,3,"Oday Oday","Pop","Rajarani");
	root=inserttolib(root,t);
}

void main(){
	int d,id,n;
	feeddata();
	do{
		n=nosongsqueued();
		printf("\n\t\tThe MusicPlayer");
		printf("\n\n1.Play/Pause\n2.Show Queued Songs\n3.Song Library\n4.Last Played");
		printf("\n5.Volume Up\n6.Volume Down");
		nowplaying();
		printf("\n7.Mute/Unmute\t\t\t");
		if(ply==1)printf("Playing");
		else printf("Paused");
		printf("\n8.Listen Next\t\t\tVolume Level: %d\n9.Listen Previous\t\tQueued Songs: %d\n0.Exit",v,n);
		printf("\nNow What do you wanna do?");
		scanf("%d",&ch);
		printf("\n");
		switch(ch){
		case 1:
			play();
			break;
		/*case 2:
			nowplaying();
			break;
		*/case 2:
			queuedsongs();
			break;
		case 3:
			library();
			printf("\nDo you wanna add a Song?(1.Yes\t0.No)");
			scanf("%d",&d);
			while(d!=0){
				printf("\nEnter the Song ID to be added:");
				scanf("%d",&id);			
				addsong(root,id);
				printf("\nThe Song is Queued.");
				printf("\nDo you wanna add a Song?(1.Yes\t0.No)");
				scanf("%d",&d);
			}
			break;
		case 4:
			lastplayed();
			break;
		case 5:
			volup();
			break;
		case 6:
			voldown();
			break;
		case 7:
			mute();
			break;
		case 8:
			playnext();
			break;
		case 9:
			playprev();
			break;
		}
		}while(ch!=0);
}
