type hook('t);
/* `wrap` should ever be exposed from the Hooks module,
   in order to keep type checks safe */
let wrap: 't => hook('t) = x => Obj.magic(x);
let unwrap: hook('t) => 't = x => Obj.magic(x);

/* let addState: (t('t), ~state: 'state) => t(('t, state('state))) =
     (x, ~state as _) => Obj.magic(x);

   let addEffect: t('t) => t(('t, effect)) = Obj.magic; */

[@bs.module "react"]
external cloneElementOther:
  (ReasonReact.reactElement, 'props) => ReasonReact.reactElement =
  "cloneElement";

module ReasonReact = {
  include ReasonReact;
  let element = (~key=?, ~ref=?, element) =>
    cloneElementOther(element, {"key": key, "ref": ref});
};

[@bs.set]
external setName: ((. 'props) => ReasonReact.reactElement, string) => unit =
  "displayName";

[@bs.module "react"] external useState: 'a => ('a, (. 'a) => unit) = "";
let useState = initialState => wrap(useState(initialState));

[@bs.module "react"]
external useEffect: (unit => (. unit) => unit) => unit = "";
[@bs.module "react"]
external useMutationEffect: (unit => (. unit) => unit) => unit = "";
[@bs.module "react"]
external useLayoutEffect: (unit => (. unit) => unit) => unit = "";

[@bs.module "react"]
external useEffectWithoutCleanup: (unit => unit) => unit = "useEffect";
[@bs.module "react"]
external useMutationEffectWithoutCleanup: (unit => unit) => unit = "";
[@bs.module "react"]
external useLayoutEffectWithoutCleanup: (unit => unit) => unit = "";

[@bs.module "react"] external useCallback: (unit => 'a, 'b, unit) => 'a = "";
[@bs.module "react"] external useMemo: (unit => 'a, 'b) => 'a = "";

[@bs.module "react"] external useRef: 'a => {. "current": 'a} = "";
[@bs.module "react"]
external useDomRef: unit => {. "current": option(Dom.node)} = "useRef";

[@bs.module "react"]
external useReducer:
  (~reducer: (. 'state, 'action) => 'state, ~initial: 'state) =>
  ('state, (. 'action) => unit) =
  "";

[@bs.module "react"]
external createElement:
  (
    ~component: (. Js.t({..} as 'a)) => ReasonReact.reactElement,
    ~props: Js.t({..} as 'a)
  ) =>
  ReasonReact.reactElement =
  "";

/* Not doing useImperativeMethods because it's super confusing. */