/* \author  Giridhar V */

// Structure to represent node of kd tree for 3D

#ifndef PLAYBACK_KDTREE3D_H
#define PLAYBACK_KDTREE3D_H

#include <pcl/impl/point_types.hpp>
#include <vector>

struct Node
{
	pcl::PointXYZI point;
	int id;
	Node* left;
	Node* right;

	Node(pcl::PointXYZI arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	void insertHelper(Node** node, uint depth, pcl::PointXYZI point, int id)
	{
        // when its NULL will insert
		if (*node == NULL)
  		    *node = new Node(point, id);
		else
		{
			uint cd = depth % 3;

            if (cd == 0) 
            {
			   if (point.x < ((*node)->point.x))
			       insertHelper(&((*node)->left), depth+1, point, id);
			   else 
			       insertHelper(&((*node)->right), depth+1, point, id);
            }
            else if (cd == 1)
            {
               if (point.y < ((*node)->point.y))
			       insertHelper(&((*node)->left), depth+1, point, id);
			   else 
			       insertHelper(&((*node)->right), depth+1, point, id);

            }
            else 
            {
                if (point.z < ((*node)->point.z))
			       insertHelper(&((*node)->left), depth+1, point, id);
			   else 
			       insertHelper(&((*node)->right), depth+1, point, id);
            }
		}
	}

	void insert(pcl::PointXYZI point, int id)
	{
		// the function should create a new node and place correctly with in the root 
		insertHelper(&root, 0, point, id);

	}

	void searchHelper(pcl::PointXYZI target, Node* node, int depth, float distanceTol, std::vector<int>& ids)
	{
		if(node!=NULL)
		{
			if( (node->point.x>=(target.x-distanceTol)&&node->point.x<=(target.x+distanceTol)) && (node->point.y>=(target.y-distanceTol)&&node->point.y<=(target.y+distanceTol)) && (node->point.z>=(target.z-distanceTol)&&node->point.z<=(target.z+distanceTol)))
			{
				float distance = sqrt((node->point.x-target.x)*(node->point.x-target.x)+(node->point.y-target.y)*(node->point.y-target.y)+(node->point.z-target.z)*(node->point.z-target.z));
				if(distance <= distanceTol)
				    ids.push_back(node->id);   
			}
            
            if (depth%3 == 0)
            {
			   if((target.x-distanceTol)<node->point.x)
			       searchHelper(target, node->left, depth+1, distanceTol, ids);
			
			   if((target.x+distanceTol)>node->point.x)
			       searchHelper(target, node->right, depth+1, distanceTol, ids);
            } else if (depth%3 == 1)
            {
               if((target.y-distanceTol)<node->point.y)
			       searchHelper(target, node->left, depth+1, distanceTol, ids);
			
			   if((target.y+distanceTol)>node->point.y)
			       searchHelper(target, node->right, depth+1, distanceTol, ids);

            } else
            {
               if((target.z-distanceTol)<node->point.z)
			       searchHelper(target, node->left, depth+1, distanceTol, ids);
			
			   if((target.z+distanceTol)>node->point.z)
			       searchHelper(target, node->right, depth+1, distanceTol, ids);                
                
            }
		}

	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(pcl::PointXYZI target, float distanceTol)
	{
		std::vector<int> ids;
		searchHelper(target, root, 0, distanceTol, ids);
		return ids;
	}
	

};

#endif  //PLAYBACK_KDTREE3D_H




