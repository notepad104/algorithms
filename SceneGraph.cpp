#include <iostream>
#include <vector>
#include <cstring>
#define __node_h_ 1 
using namespace std;

class Node
{
    private:
        Node* m_Parent;
        const char* m_Name;
        vector<Node* > m_Children;
    public:
        Node(Node* Parent = NULL, const char* Name = NULL) : m_Name(Name)
        {
            m_Parent = Parent;
        }
        ~Node()
        {
            m_Parent = NULL;
            m_Children.clear();
        }
        void Update()
        {
            if (!m_Children.empty())
            {
                for (size_t i = 0; i < m_Children.size(); ++i)
                {
                    if (NULL != m_Children[i])
                    {
                        m_Children[i]->Update();
                    }
                }
            }
        }
     
        Node* GetParentNode(void) const
        {
            return m_Parent;
        }
        
        void SetParentNode(Node* NewParent)
        {
            if (NULL != m_Parent)
            {
                m_Parent->RemoveChildNode(this);
            }
            m_Parent = NewParent;
        }
     
        void AddChildNode(Node* ChildNode)
        {
            if (NULL != ChildNode)
            {
                if (NULL != ChildNode->GetParentNode())
                {
                    ChildNode->SetParentNode(this);
                }
                m_Children.push_back(ChildNode);
            }
        }
        
        void RemoveChildNode(Node* ChildNode)
        {
            if (NULL != ChildNode && !m_Children.empty())
            {
                for (size_t i = 0; i < m_Children.size(); ++i)
                {
                    if (m_Children[i] == ChildNode)
                    {
                        m_Children.erase(m_Children.begin() + i);
                        break;
                    }
                }
            }
        }
     
        const char* GetNodeName(void) const
        {
            return m_Name;
        }
        const size_t CountChildNodes(const bool& RecursiveCount) const
        {
            if (!RecursiveCount)
            {
                return(m_Children.size());
            }
            else
            {
                size_t Retval = m_Children.size();
                for (size_t i = 0; i < m_Children.size(); ++i)
                {
                    Retval += m_Children[i]->CountChildNodes(true);
                }
                return(Retval);
            }
        }
        //virtual const bool IsRootNode() const = 0;
     
        Node* GetChildNodeByName(const char* SearchName)
        {
            Node* Retval = NULL;
            if(!m_Children.empty())
            {
                for (size_t i = 0; i < m_Children.size(); ++i)
                {
                    if (0 == strcmp(m_Children[i]->m_Name, SearchName))
                    {
                        Retval = m_Children[i];
                        break;
                    }
                }
            }
            return(Retval);
        }
};

int main()
{
    Node sg(NULL,"shubham");
    
    return 0;
}
