
#if defined(BOOST_HAS_TEMPLATE_ALIASES) && defined(BOOST_HAS_DECLTYPE)
    template<typename T> using QFSM_BIND = QFsm::Front::Operations::Bind<decltype(T), T>;
#else
#   ifdef __GNUC__
#       pragma GCC system_header
#   endif
#   define QFSM_BIND(...) QFsm::Front::Operations::Bind<BOOST_TYPEOF(__VA_ARGS__), __VA_ARGS__>
#endif

template<typename T, T Func, typename Enable = void>
class Bind : public Detail::AcquireDynamic<T, Func, typename Detail::Functor<T>::Result, typename Detail::Functor<T>::Base>,  Back::Aux::Operation1<typename Detail::Functor<T>::Base>
{ };

template<typename T, T Func>
class Bind<T, Func, typename boost::enable_if< boost::is_same<typename Detail::Functor<T>::Base, void> >::type> : public Detail::AcquireStatic<T, Func, typename Detail::Functor<T>::Result>
{ };
