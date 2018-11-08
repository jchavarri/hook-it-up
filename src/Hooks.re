[@bs.module "react"]
external cloneElementOther:
  (ReasonReact.reactElement, 'props) => ReasonReact.reactElement =
  "cloneElement";

module ReasonReact = {
  include ReasonReact;
  let element = (~key=?, ~ref=?, element) =>
    cloneElementOther(element, {"key": key, "ref": ref});
};

[@bs.set] external setName: ((. 'props) => ReasonReact.reactElement, string) => unit = "displayName";

type reactHook('a) =
  | Hook('a);
let map = (Hook(a), f) => Hook(f(a));

[@bs.module "react"] external useState: 'a => ('a, (. 'a) => unit) = "";
let useState = a => Hook(useState(a));

[@bs.module "react"] external useEffect: ((unit) => ((. unit) => unit)) => unit = "";
[@bs.module "react"]
external useMutationEffect: ((unit) => ((. unit) => unit)) => unit = "";
[@bs.module "react"]
external useLayoutEffect: ((unit) => ((. unit) => unit)) => unit = "";

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

/* let unwrapHook: t('t) => t(('t, effect)) = Obj.magic; */
let rec createElementWithHookedComponent = (~component, ~props) =>
  switch (component) {
  | Hook(Hook(a)) =>
    createElementWithHookedComponent(~component=(Hook(a)), ~props)
  | Hook(a) => createElement(a)
  };
/* Not doing useImperativeMethods because it's super confusing. */