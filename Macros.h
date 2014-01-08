#ifndef MACROS_H_
#define MACROS_H_

#define GET(Type, MemberName, FaceName) \
	Type get##FaceName() const { \
		return MemberName; \
	};

#define SET(Type, MemberName, FaceName) \
	void set##FaceName(Type value) { \
		MemberName = value; \
	};

#define SET_CONST_REF(Type, MemberName, FaceName) \
	void set##FaceName(const Type& value) { \
		MemberName = value; \
	};

#define GET_CONST_REF(Type, MemberName, FaceName) \
	const Type& get##FaceName() const { \
		return MemberName; \
	};

#define GETSET(Type, MemberName, FaceName) \
	Type get##FaceName() const { \
		return MemberName; \
	}; \
	\
	void set##FaceName(Type value) { \
		MemberName = value; \
	};

#define GETSET_CONST_REF(Type, MemberName, FaceName) \
	const Type& get##FaceName() const { \
		return MemberName; \
	}; \
	\
	void set##FaceName(const Type& value) { \
		MemberName = value; \
	};

#define GETSET_INTERFACE(Type, FaceName) \
	virtual Type get##FaceName() const = 0; \
	\
	virtual void set##FaceName(Type value) = 0;

/*
#define GETSET(ClassName, Type, MemberName, FaceName) \
	Type ClassName::get##FaceName() const { \
		return MemberName; \
	}; \
	\
	void ClassName::set##FaceName(Type value) { \
		MemberName = value; \
	}
*/

#endif /* MACROS_H_ */
