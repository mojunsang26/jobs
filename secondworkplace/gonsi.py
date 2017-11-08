
# coding: utf-8

# In[1]:


from bs4 import BeautifulSoup


# In[2]:


import urllib.request as req


# In[4]:


url = "http://www.schoolinfo.go.kr/ei/pp/Pneipp_a01_s2.do"
res = req.urlopen(url)
soup = BeautifulSoup(res,"html.parser")


# In[8]:


a_list = soup.select("div.DataTable>table.TableType1>tbody>tr td")


# In[10]:


for td in a_list:
    print(td.string)


# In[11]:


type(a_list)


# In[12]:


a_list

