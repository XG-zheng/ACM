struct hashFun{
	template<typename T,typename U>
	size_t operator() (const pair<T,U> &i)const{
		return hash<T>()(i.fi)^hash<U>()(i.se);
	}
};
unordered_map<pii,int,hashFun> M;
