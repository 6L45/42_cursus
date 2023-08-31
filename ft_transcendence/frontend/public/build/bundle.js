
(function(l, r) { if (!l || l.getElementById('livereloadscript')) return; r = l.createElement('script'); r.async = 1; r.src = '//' + (self.location.host || 'localhost').split(':')[0] + ':35729/livereload.js?snipver=1'; r.id = 'livereloadscript'; l.getElementsByTagName('head')[0].appendChild(r) })(self.document);
var app = (function (environment, colyseus_js) {
    'use strict';

    function noop$1() { }
    // Adapted from https://github.com/then/is-promise/blob/master/index.js
    // Distributed under MIT License https://github.com/then/is-promise/blob/master/LICENSE
    function is_promise(value) {
        return !!value && (typeof value === 'object' || typeof value === 'function') && typeof value.then === 'function';
    }
    function add_location(element, file, line, column, char) {
        element.__svelte_meta = {
            loc: { file, line, column, char }
        };
    }
    function run(fn) {
        return fn();
    }
    function blank_object() {
        return Object.create(null);
    }
    function run_all(fns) {
        fns.forEach(run);
    }
    function is_function(thing) {
        return typeof thing === 'function';
    }
    function safe_not_equal(a, b) {
        return a != a ? b == b : a !== b || ((a && typeof a === 'object') || typeof a === 'function');
    }
    let src_url_equal_anchor;
    function src_url_equal(element_src, url) {
        if (!src_url_equal_anchor) {
            src_url_equal_anchor = document.createElement('a');
        }
        src_url_equal_anchor.href = url;
        return element_src === src_url_equal_anchor.href;
    }
    function is_empty(obj) {
        return Object.keys(obj).length === 0;
    }
    function validate_store(store, name) {
        if (store != null && typeof store.subscribe !== 'function') {
            throw new Error(`'${name}' is not a store with a 'subscribe' method`);
        }
    }
    function subscribe(store, ...callbacks) {
        if (store == null) {
            return noop$1;
        }
        const unsub = store.subscribe(...callbacks);
        return unsub.unsubscribe ? () => unsub.unsubscribe() : unsub;
    }
    function get_store_value(store) {
        let value;
        subscribe(store, _ => value = _)();
        return value;
    }
    function component_subscribe(component, store, callback) {
        component.$$.on_destroy.push(subscribe(store, callback));
    }
    function set_store_value(store, ret, value) {
        store.set(value);
        return ret;
    }

    new Set();

    const globals = (typeof window !== 'undefined'
        ? window
        : typeof globalThis !== 'undefined'
            ? globalThis
            : global);
    // Needs to be written like this to pass the tree-shake-test
    'WeakMap' in globals ? new WeakMap() : undefined;
    function append(target, node) {
        target.appendChild(node);
    }
    function insert(target, node, anchor) {
        target.insertBefore(node, anchor || null);
    }
    function detach(node) {
        if (node.parentNode) {
            node.parentNode.removeChild(node);
        }
    }
    function destroy_each(iterations, detaching) {
        for (let i = 0; i < iterations.length; i += 1) {
            if (iterations[i])
                iterations[i].d(detaching);
        }
    }
    function element(name) {
        return document.createElement(name);
    }
    function text(data) {
        return document.createTextNode(data);
    }
    function space() {
        return text(' ');
    }
    function empty$1() {
        return text('');
    }
    function listen(node, event, handler, options) {
        node.addEventListener(event, handler, options);
        return () => node.removeEventListener(event, handler, options);
    }
    function prevent_default(fn) {
        return function (event) {
            event.preventDefault();
            // @ts-ignore
            return fn.call(this, event);
        };
    }
    function self$1(fn) {
        return function (event) {
            // @ts-ignore
            if (event.target === this)
                fn.call(this, event);
        };
    }
    function attr(node, attribute, value) {
        if (value == null)
            node.removeAttribute(attribute);
        else if (node.getAttribute(attribute) !== value)
            node.setAttribute(attribute, value);
    }
    function children(element) {
        return Array.from(element.childNodes);
    }
    function set_data(text, data) {
        data = '' + data;
        if (text.data === data)
            return;
        text.data = data;
    }
    function set_input_value(input, value) {
        input.value = value == null ? '' : value;
    }
    function set_style(node, key, value, important) {
        if (value == null) {
            node.style.removeProperty(key);
        }
        else {
            node.style.setProperty(key, value, important ? 'important' : '');
        }
    }
    function select_option(select, value, mounting) {
        for (let i = 0; i < select.options.length; i += 1) {
            const option = select.options[i];
            if (option.__value === value) {
                option.selected = true;
                return;
            }
        }
        if (!mounting || value !== undefined) {
            select.selectedIndex = -1; // no option should be selected
        }
    }
    function select_value(select) {
        const selected_option = select.querySelector(':checked');
        return selected_option && selected_option.__value;
    }
    function toggle_class(element, name, toggle) {
        element.classList[toggle ? 'add' : 'remove'](name);
    }
    function custom_event(type, detail, { bubbles = false, cancelable = false } = {}) {
        const e = document.createEvent('CustomEvent');
        e.initCustomEvent(type, bubbles, cancelable, detail);
        return e;
    }

    // we need to store the information for multiple documents because a Svelte application could also contain iframes
    // https://github.com/sveltejs/svelte/issues/3624
    new Map();

    let current_component;
    function set_current_component(component) {
        current_component = component;
    }
    function get_current_component() {
        if (!current_component)
            throw new Error('Function called outside component initialization');
        return current_component;
    }
    /**
     * The `onMount` function schedules a callback to run as soon as the component has been mounted to the DOM.
     * It must be called during the component's initialisation (but doesn't need to live *inside* the component;
     * it can be called from an external module).
     *
     * `onMount` does not run inside a [server-side component](/docs#run-time-server-side-component-api).
     *
     * https://svelte.dev/docs#run-time-svelte-onmount
     */
    function onMount(fn) {
        get_current_component().$$.on_mount.push(fn);
    }
    /**
     * Schedules a callback to run immediately after the component has been updated.
     *
     * The first time the callback runs will be after the initial `onMount`
     */
    function afterUpdate(fn) {
        get_current_component().$$.after_update.push(fn);
    }
    /**
     * Schedules a callback to run immediately before the component is unmounted.
     *
     * Out of `onMount`, `beforeUpdate`, `afterUpdate` and `onDestroy`, this is the
     * only one that runs inside a server-side component.
     *
     * https://svelte.dev/docs#run-time-svelte-ondestroy
     */
    function onDestroy(fn) {
        get_current_component().$$.on_destroy.push(fn);
    }
    /**
     * Creates an event dispatcher that can be used to dispatch [component events](/docs#template-syntax-component-directives-on-eventname).
     * Event dispatchers are functions that can take two arguments: `name` and `detail`.
     *
     * Component events created with `createEventDispatcher` create a
     * [CustomEvent](https://developer.mozilla.org/en-US/docs/Web/API/CustomEvent).
     * These events do not [bubble](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Building_blocks/Events#Event_bubbling_and_capture).
     * The `detail` argument corresponds to the [CustomEvent.detail](https://developer.mozilla.org/en-US/docs/Web/API/CustomEvent/detail)
     * property and can contain any type of data.
     *
     * https://svelte.dev/docs#run-time-svelte-createeventdispatcher
     */
    function createEventDispatcher() {
        const component = get_current_component();
        return (type, detail, { cancelable = false } = {}) => {
            const callbacks = component.$$.callbacks[type];
            if (callbacks) {
                // TODO are there situations where events could be dispatched
                // in a server (non-DOM) environment?
                const event = custom_event(type, detail, { cancelable });
                callbacks.slice().forEach(fn => {
                    fn.call(component, event);
                });
                return !event.defaultPrevented;
            }
            return true;
        };
    }
    // TODO figure out if we still want to support
    // shorthand events, or if we want to implement
    // a real bubbling mechanism
    function bubble(component, event) {
        const callbacks = component.$$.callbacks[event.type];
        if (callbacks) {
            // @ts-ignore
            callbacks.slice().forEach(fn => fn.call(this, event));
        }
    }

    const dirty_components = [];
    const binding_callbacks = [];
    let render_callbacks = [];
    const flush_callbacks = [];
    const resolved_promise = /* @__PURE__ */ Promise.resolve();
    let update_scheduled = false;
    function schedule_update() {
        if (!update_scheduled) {
            update_scheduled = true;
            resolved_promise.then(flush);
        }
    }
    function add_render_callback(fn) {
        render_callbacks.push(fn);
    }
    function add_flush_callback(fn) {
        flush_callbacks.push(fn);
    }
    // flush() calls callbacks in this order:
    // 1. All beforeUpdate callbacks, in order: parents before children
    // 2. All bind:this callbacks, in reverse order: children before parents.
    // 3. All afterUpdate callbacks, in order: parents before children. EXCEPT
    //    for afterUpdates called during the initial onMount, which are called in
    //    reverse order: children before parents.
    // Since callbacks might update component values, which could trigger another
    // call to flush(), the following steps guard against this:
    // 1. During beforeUpdate, any updated components will be added to the
    //    dirty_components array and will cause a reentrant call to flush(). Because
    //    the flush index is kept outside the function, the reentrant call will pick
    //    up where the earlier call left off and go through all dirty components. The
    //    current_component value is saved and restored so that the reentrant call will
    //    not interfere with the "parent" flush() call.
    // 2. bind:this callbacks cannot trigger new flush() calls.
    // 3. During afterUpdate, any updated components will NOT have their afterUpdate
    //    callback called a second time; the seen_callbacks set, outside the flush()
    //    function, guarantees this behavior.
    const seen_callbacks = new Set();
    let flushidx = 0; // Do *not* move this inside the flush() function
    function flush() {
        // Do not reenter flush while dirty components are updated, as this can
        // result in an infinite loop. Instead, let the inner flush handle it.
        // Reentrancy is ok afterwards for bindings etc.
        if (flushidx !== 0) {
            return;
        }
        const saved_component = current_component;
        do {
            // first, call beforeUpdate functions
            // and update components
            try {
                while (flushidx < dirty_components.length) {
                    const component = dirty_components[flushidx];
                    flushidx++;
                    set_current_component(component);
                    update(component.$$);
                }
            }
            catch (e) {
                // reset dirty state to not end up in a deadlocked state and then rethrow
                dirty_components.length = 0;
                flushidx = 0;
                throw e;
            }
            set_current_component(null);
            dirty_components.length = 0;
            flushidx = 0;
            while (binding_callbacks.length)
                binding_callbacks.pop()();
            // then, once components are updated, call
            // afterUpdate functions. This may cause
            // subsequent updates...
            for (let i = 0; i < render_callbacks.length; i += 1) {
                const callback = render_callbacks[i];
                if (!seen_callbacks.has(callback)) {
                    // ...so guard against infinite loops
                    seen_callbacks.add(callback);
                    callback();
                }
            }
            render_callbacks.length = 0;
        } while (dirty_components.length);
        while (flush_callbacks.length) {
            flush_callbacks.pop()();
        }
        update_scheduled = false;
        seen_callbacks.clear();
        set_current_component(saved_component);
    }
    function update($$) {
        if ($$.fragment !== null) {
            $$.update();
            run_all($$.before_update);
            const dirty = $$.dirty;
            $$.dirty = [-1];
            $$.fragment && $$.fragment.p($$.ctx, dirty);
            $$.after_update.forEach(add_render_callback);
        }
    }
    /**
     * Useful for example to execute remaining `afterUpdate` callbacks before executing `destroy`.
     */
    function flush_render_callbacks(fns) {
        const filtered = [];
        const targets = [];
        render_callbacks.forEach((c) => fns.indexOf(c) === -1 ? filtered.push(c) : targets.push(c));
        targets.forEach((c) => c());
        render_callbacks = filtered;
    }
    const outroing = new Set();
    let outros;
    function group_outros() {
        outros = {
            r: 0,
            c: [],
            p: outros // parent group
        };
    }
    function check_outros() {
        if (!outros.r) {
            run_all(outros.c);
        }
        outros = outros.p;
    }
    function transition_in(block, local) {
        if (block && block.i) {
            outroing.delete(block);
            block.i(local);
        }
    }
    function transition_out(block, local, detach, callback) {
        if (block && block.o) {
            if (outroing.has(block))
                return;
            outroing.add(block);
            outros.c.push(() => {
                outroing.delete(block);
                if (callback) {
                    if (detach)
                        block.d(1);
                    callback();
                }
            });
            block.o(local);
        }
        else if (callback) {
            callback();
        }
    }

    function handle_promise(promise, info) {
        const token = info.token = {};
        function update(type, index, key, value) {
            if (info.token !== token)
                return;
            info.resolved = value;
            let child_ctx = info.ctx;
            if (key !== undefined) {
                child_ctx = child_ctx.slice();
                child_ctx[key] = value;
            }
            const block = type && (info.current = type)(child_ctx);
            let needs_flush = false;
            if (info.block) {
                if (info.blocks) {
                    info.blocks.forEach((block, i) => {
                        if (i !== index && block) {
                            group_outros();
                            transition_out(block, 1, 1, () => {
                                if (info.blocks[i] === block) {
                                    info.blocks[i] = null;
                                }
                            });
                            check_outros();
                        }
                    });
                }
                else {
                    info.block.d(1);
                }
                block.c();
                transition_in(block, 1);
                block.m(info.mount(), info.anchor);
                needs_flush = true;
            }
            info.block = block;
            if (info.blocks)
                info.blocks[index] = block;
            if (needs_flush) {
                flush();
            }
        }
        if (is_promise(promise)) {
            const current_component = get_current_component();
            promise.then(value => {
                set_current_component(current_component);
                update(info.then, 1, info.value, value);
                set_current_component(null);
            }, error => {
                set_current_component(current_component);
                update(info.catch, 2, info.error, error);
                set_current_component(null);
                if (!info.hasCatch) {
                    throw error;
                }
            });
            // if we previously had a then/catch block, destroy it
            if (info.current !== info.pending) {
                update(info.pending, 0);
                return true;
            }
        }
        else {
            if (info.current !== info.then) {
                update(info.then, 1, info.value, promise);
                return true;
            }
            info.resolved = promise;
        }
    }
    function update_await_block_branch(info, ctx, dirty) {
        const child_ctx = ctx.slice();
        const { resolved } = info;
        if (info.current === info.then) {
            child_ctx[info.value] = resolved;
        }
        if (info.current === info.catch) {
            child_ctx[info.error] = resolved;
        }
        info.block.p(child_ctx, dirty);
    }

    function destroy_block(block, lookup) {
        block.d(1);
        lookup.delete(block.key);
    }
    function update_keyed_each(old_blocks, dirty, get_key, dynamic, ctx, list, lookup, node, destroy, create_each_block, next, get_context) {
        let o = old_blocks.length;
        let n = list.length;
        let i = o;
        const old_indexes = {};
        while (i--)
            old_indexes[old_blocks[i].key] = i;
        const new_blocks = [];
        const new_lookup = new Map();
        const deltas = new Map();
        const updates = [];
        i = n;
        while (i--) {
            const child_ctx = get_context(ctx, list, i);
            const key = get_key(child_ctx);
            let block = lookup.get(key);
            if (!block) {
                block = create_each_block(key, child_ctx);
                block.c();
            }
            else if (dynamic) {
                // defer updates until all the DOM shuffling is done
                updates.push(() => block.p(child_ctx, dirty));
            }
            new_lookup.set(key, new_blocks[i] = block);
            if (key in old_indexes)
                deltas.set(key, Math.abs(i - old_indexes[key]));
        }
        const will_move = new Set();
        const did_move = new Set();
        function insert(block) {
            transition_in(block, 1);
            block.m(node, next);
            lookup.set(block.key, block);
            next = block.first;
            n--;
        }
        while (o && n) {
            const new_block = new_blocks[n - 1];
            const old_block = old_blocks[o - 1];
            const new_key = new_block.key;
            const old_key = old_block.key;
            if (new_block === old_block) {
                // do nothing
                next = new_block.first;
                o--;
                n--;
            }
            else if (!new_lookup.has(old_key)) {
                // remove old block
                destroy(old_block, lookup);
                o--;
            }
            else if (!lookup.has(new_key) || will_move.has(new_key)) {
                insert(new_block);
            }
            else if (did_move.has(old_key)) {
                o--;
            }
            else if (deltas.get(new_key) > deltas.get(old_key)) {
                did_move.add(new_key);
                insert(new_block);
            }
            else {
                will_move.add(old_key);
                o--;
            }
        }
        while (o--) {
            const old_block = old_blocks[o];
            if (!new_lookup.has(old_block.key))
                destroy(old_block, lookup);
        }
        while (n)
            insert(new_blocks[n - 1]);
        run_all(updates);
        return new_blocks;
    }
    function validate_each_keys(ctx, list, get_context, get_key) {
        const keys = new Set();
        for (let i = 0; i < list.length; i++) {
            const key = get_key(get_context(ctx, list, i));
            if (keys.has(key)) {
                throw new Error('Cannot have duplicate keys in a keyed each');
            }
            keys.add(key);
        }
    }

    const _boolean_attributes = [
        'allowfullscreen',
        'allowpaymentrequest',
        'async',
        'autofocus',
        'autoplay',
        'checked',
        'controls',
        'default',
        'defer',
        'disabled',
        'formnovalidate',
        'hidden',
        'inert',
        'ismap',
        'loop',
        'multiple',
        'muted',
        'nomodule',
        'novalidate',
        'open',
        'playsinline',
        'readonly',
        'required',
        'reversed',
        'selected'
    ];
    /**
     * List of HTML boolean attributes (e.g. `<input disabled>`).
     * Source: https://html.spec.whatwg.org/multipage/indices.html
     */
    new Set([..._boolean_attributes]);

    function bind$1(component, name, callback) {
        const index = component.$$.props[name];
        if (index !== undefined) {
            component.$$.bound[index] = callback;
            callback(component.$$.ctx[index]);
        }
    }
    function create_component(block) {
        block && block.c();
    }
    function mount_component(component, target, anchor, customElement) {
        const { fragment, after_update } = component.$$;
        fragment && fragment.m(target, anchor);
        if (!customElement) {
            // onMount happens before the initial afterUpdate
            add_render_callback(() => {
                const new_on_destroy = component.$$.on_mount.map(run).filter(is_function);
                // if the component was destroyed immediately
                // it will update the `$$.on_destroy` reference to `null`.
                // the destructured on_destroy may still reference to the old array
                if (component.$$.on_destroy) {
                    component.$$.on_destroy.push(...new_on_destroy);
                }
                else {
                    // Edge case - component was destroyed immediately,
                    // most likely as a result of a binding initialising
                    run_all(new_on_destroy);
                }
                component.$$.on_mount = [];
            });
        }
        after_update.forEach(add_render_callback);
    }
    function destroy_component(component, detaching) {
        const $$ = component.$$;
        if ($$.fragment !== null) {
            flush_render_callbacks($$.after_update);
            run_all($$.on_destroy);
            $$.fragment && $$.fragment.d(detaching);
            // TODO null out other refs, including component.$$ (but need to
            // preserve final state?)
            $$.on_destroy = $$.fragment = null;
            $$.ctx = [];
        }
    }
    function make_dirty(component, i) {
        if (component.$$.dirty[0] === -1) {
            dirty_components.push(component);
            schedule_update();
            component.$$.dirty.fill(0);
        }
        component.$$.dirty[(i / 31) | 0] |= (1 << (i % 31));
    }
    function init(component, options, instance, create_fragment, not_equal, props, append_styles, dirty = [-1]) {
        const parent_component = current_component;
        set_current_component(component);
        const $$ = component.$$ = {
            fragment: null,
            ctx: [],
            // state
            props,
            update: noop$1,
            not_equal,
            bound: blank_object(),
            // lifecycle
            on_mount: [],
            on_destroy: [],
            on_disconnect: [],
            before_update: [],
            after_update: [],
            context: new Map(options.context || (parent_component ? parent_component.$$.context : [])),
            // everything else
            callbacks: blank_object(),
            dirty,
            skip_bound: false,
            root: options.target || parent_component.$$.root
        };
        append_styles && append_styles($$.root);
        let ready = false;
        $$.ctx = instance
            ? instance(component, options.props || {}, (i, ret, ...rest) => {
                const value = rest.length ? rest[0] : ret;
                if ($$.ctx && not_equal($$.ctx[i], $$.ctx[i] = value)) {
                    if (!$$.skip_bound && $$.bound[i])
                        $$.bound[i](value);
                    if (ready)
                        make_dirty(component, i);
                }
                return ret;
            })
            : [];
        $$.update();
        ready = true;
        run_all($$.before_update);
        // `false` as a special case of no DOM component
        $$.fragment = create_fragment ? create_fragment($$.ctx) : false;
        if (options.target) {
            if (options.hydrate) {
                const nodes = children(options.target);
                // eslint-disable-next-line @typescript-eslint/no-non-null-assertion
                $$.fragment && $$.fragment.l(nodes);
                nodes.forEach(detach);
            }
            else {
                // eslint-disable-next-line @typescript-eslint/no-non-null-assertion
                $$.fragment && $$.fragment.c();
            }
            if (options.intro)
                transition_in(component.$$.fragment);
            mount_component(component, options.target, options.anchor, options.customElement);
            flush();
        }
        set_current_component(parent_component);
    }
    /**
     * Base class for Svelte components. Used when dev=false.
     */
    class SvelteComponent {
        $destroy() {
            destroy_component(this, 1);
            this.$destroy = noop$1;
        }
        $on(type, callback) {
            if (!is_function(callback)) {
                return noop$1;
            }
            const callbacks = (this.$$.callbacks[type] || (this.$$.callbacks[type] = []));
            callbacks.push(callback);
            return () => {
                const index = callbacks.indexOf(callback);
                if (index !== -1)
                    callbacks.splice(index, 1);
            };
        }
        $set($$props) {
            if (this.$$set && !is_empty($$props)) {
                this.$$.skip_bound = true;
                this.$$set($$props);
                this.$$.skip_bound = false;
            }
        }
    }

    function dispatch_dev(type, detail) {
        document.dispatchEvent(custom_event(type, Object.assign({ version: '3.59.1' }, detail), { bubbles: true }));
    }
    function append_dev(target, node) {
        dispatch_dev('SvelteDOMInsert', { target, node });
        append(target, node);
    }
    function insert_dev(target, node, anchor) {
        dispatch_dev('SvelteDOMInsert', { target, node, anchor });
        insert(target, node, anchor);
    }
    function detach_dev(node) {
        dispatch_dev('SvelteDOMRemove', { node });
        detach(node);
    }
    function listen_dev(node, event, handler, options, has_prevent_default, has_stop_propagation, has_stop_immediate_propagation) {
        const modifiers = options === true ? ['capture'] : options ? Array.from(Object.keys(options)) : [];
        if (has_prevent_default)
            modifiers.push('preventDefault');
        if (has_stop_propagation)
            modifiers.push('stopPropagation');
        if (has_stop_immediate_propagation)
            modifiers.push('stopImmediatePropagation');
        dispatch_dev('SvelteDOMAddEventListener', { node, event, handler, modifiers });
        const dispose = listen(node, event, handler, options);
        return () => {
            dispatch_dev('SvelteDOMRemoveEventListener', { node, event, handler, modifiers });
            dispose();
        };
    }
    function attr_dev(node, attribute, value) {
        attr(node, attribute, value);
        if (value == null)
            dispatch_dev('SvelteDOMRemoveAttribute', { node, attribute });
        else
            dispatch_dev('SvelteDOMSetAttribute', { node, attribute, value });
    }
    function prop_dev(node, property, value) {
        node[property] = value;
        dispatch_dev('SvelteDOMSetProperty', { node, property, value });
    }
    function dataset_dev(node, property, value) {
        node.dataset[property] = value;
        dispatch_dev('SvelteDOMSetDataset', { node, property, value });
    }
    function set_data_dev(text, data) {
        data = '' + data;
        if (text.data === data)
            return;
        dispatch_dev('SvelteDOMSetData', { node: text, data });
        text.data = data;
    }
    function validate_each_argument(arg) {
        if (typeof arg !== 'string' && !(arg && typeof arg === 'object' && 'length' in arg)) {
            let msg = '{#each} only iterates over array-like objects.';
            if (typeof Symbol === 'function' && arg && Symbol.iterator in arg) {
                msg += ' You can use a spread to convert this iterable into an array.';
            }
            throw new Error(msg);
        }
    }
    function validate_slots(name, slot, keys) {
        for (const slot_key of Object.keys(slot)) {
            if (!~keys.indexOf(slot_key)) {
                console.warn(`<${name}> received an unexpected slot "${slot_key}".`);
            }
        }
    }
    /**
     * Base class for Svelte components with some minor dev-enhancements. Used when dev=true.
     */
    class SvelteComponentDev extends SvelteComponent {
        constructor(options) {
            if (!options || (!options.target && !options.$$inline)) {
                throw new Error("'target' is a required option");
            }
            super();
        }
        $destroy() {
            super.$destroy();
            this.$destroy = () => {
                console.warn('Component was already destroyed'); // eslint-disable-line no-console
            };
        }
        $capture_state() { }
        $inject_state() { }
    }

    const hostname = "c3r2p2";

    /* src/component/login/Login.svelte generated by Svelte v3.59.1 */
    const file$i = "src/component/login/Login.svelte";

    function create_fragment$i(ctx) {
    	let form;
    	let a;
    	let t;

    	const block = {
    		c: function create() {
    			form = element("form");
    			a = element("a");
    			t = text("Sign in with 42");
    			attr_dev(a, "href", /*url*/ ctx[0]);
    			attr_dev(a, "class", "login-button svelte-9tkyhx");
    			add_location(a, file$i, 41, 4, 990);
    			attr_dev(form, "class", "svelte-9tkyhx");
    			add_location(form, file$i, 40, 0, 979);
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, form, anchor);
    			append_dev(form, a);
    			append_dev(a, t);
    		},
    		p: noop$1,
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(form);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$i.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$i($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Login', slots, []);
    	const url = `https://api.intra.42.fr/oauth/authorize?client_id=u-s4t2ud-57f53bc679ac4357e6818e8b726b84b6af288c76553560350ca07ecc5a8d7a87&redirect_uri=http%3A%2F%2F${hostname}%3A3000%2Fauth&response_type=code`;
    	const writable_props = [];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console.warn(`<Login> was created with unknown prop '${key}'`);
    	});

    	$$self.$capture_state = () => ({ hostname, url });
    	return [url];
    }

    class Login extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$i, create_fragment$i, safe_not_equal, {});

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Login",
    			options,
    			id: create_fragment$i.name
    		});
    	}
    }

    /* src/component/dfa/dfaHomePage.svelte generated by Svelte v3.59.1 */

    const { console: console_1$b } = globals;
    const file$h = "src/component/dfa/dfaHomePage.svelte";

    function create_fragment$h(ctx) {
    	let main;
    	let h1;
    	let t1;
    	let form;
    	let label;
    	let t3;
    	let input;
    	let t4;
    	let button;
    	let mounted;
    	let dispose;

    	const block = {
    		c: function create() {
    			main = element("main");
    			h1 = element("h1");
    			h1.textContent = "Welcome to DFA Homepage!";
    			t1 = space();
    			form = element("form");
    			label = element("label");
    			label.textContent = "Enter your 2FA code:";
    			t3 = space();
    			input = element("input");
    			t4 = space();
    			button = element("button");
    			button.textContent = "Submit";
    			attr_dev(h1, "class", "svelte-1q0604z");
    			add_location(h1, file$h, 53, 4, 1392);
    			attr_dev(label, "for", "code");
    			attr_dev(label, "class", "svelte-1q0604z");
    			add_location(label, file$h, 55, 6, 1483);
    			attr_dev(input, "type", "text");
    			attr_dev(input, "id", "code");
    			attr_dev(input, "class", "svelte-1q0604z");
    			add_location(input, file$h, 56, 6, 1536);
    			attr_dev(button, "type", "submit");
    			attr_dev(button, "class", "svelte-1q0604z");
    			add_location(button, file$h, 57, 6, 1592);
    			attr_dev(form, "class", "svelte-1q0604z");
    			add_location(form, file$h, 54, 4, 1430);
    			attr_dev(main, "class", "svelte-1q0604z");
    			add_location(main, file$h, 52, 2, 1381);
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, main, anchor);
    			append_dev(main, h1);
    			append_dev(main, t1);
    			append_dev(main, form);
    			append_dev(form, label);
    			append_dev(form, t3);
    			append_dev(form, input);
    			set_input_value(input, /*code*/ ctx[0]);
    			append_dev(form, t4);
    			append_dev(form, button);

    			if (!mounted) {
    				dispose = [
    					listen_dev(input, "input", /*input_input_handler*/ ctx[4]),
    					listen_dev(form, "submit", prevent_default(/*handleSubmit*/ ctx[1]), false, true, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(ctx, [dirty]) {
    			if (dirty & /*code*/ 1 && input.value !== /*code*/ ctx[0]) {
    				set_input_value(input, /*code*/ ctx[0]);
    			}
    		},
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(main);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$h.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$h($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('DfaHomePage', slots, []);
    	let { data } = $$props;
    	let { isDFAActive } = $$props;
    	const dispatch = createEventDispatcher();
    	let id = data.id;
    	let code = ""; // variable to store the user's 2FA code

    	async function handleSubmit() {
    		console.log(code);
    		const url = `http://${hostname}:3000/auth/2fa/verify/${id}`;

    		const params = {
    			method: "POST",
    			headers: { 'Content-Type': 'application/json' },
    			body: JSON.stringify({ code, id: data.id })
    		};

    		fetch(url, params).then(async res => {
    			const value = await res.json();

    			if (res.status == 201) {
    				console.log("ces good");
    				$$invalidate(2, isDFAActive = false);
    				console.log("pas de catch");
    			} else {
    				console.log("pas good");
    			}

    			console.log(value.message);
    		}).catch(err => {
    			console.log("ERROR: " + err);
    			console.error("Le back ne repond pas");
    		});
    	}

    	onMount(() => {
    		console.log('in Dfa');
    		$$invalidate(0, code = "");
    	});

    	$$self.$$.on_mount.push(function () {
    		if (data === undefined && !('data' in $$props || $$self.$$.bound[$$self.$$.props['data']])) {
    			console_1$b.warn("<DfaHomePage> was created without expected prop 'data'");
    		}

    		if (isDFAActive === undefined && !('isDFAActive' in $$props || $$self.$$.bound[$$self.$$.props['isDFAActive']])) {
    			console_1$b.warn("<DfaHomePage> was created without expected prop 'isDFAActive'");
    		}
    	});

    	const writable_props = ['data', 'isDFAActive'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console_1$b.warn(`<DfaHomePage> was created with unknown prop '${key}'`);
    	});

    	function input_input_handler() {
    		code = this.value;
    		$$invalidate(0, code);
    	}

    	$$self.$$set = $$props => {
    		if ('data' in $$props) $$invalidate(3, data = $$props.data);
    		if ('isDFAActive' in $$props) $$invalidate(2, isDFAActive = $$props.isDFAActive);
    	};

    	$$self.$capture_state = () => ({
    		onMount,
    		hostname,
    		onDestroy,
    		createEventDispatcher,
    		data,
    		isDFAActive,
    		dispatch,
    		id,
    		code,
    		handleSubmit
    	});

    	$$self.$inject_state = $$props => {
    		if ('data' in $$props) $$invalidate(3, data = $$props.data);
    		if ('isDFAActive' in $$props) $$invalidate(2, isDFAActive = $$props.isDFAActive);
    		if ('id' in $$props) id = $$props.id;
    		if ('code' in $$props) $$invalidate(0, code = $$props.code);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [code, handleSubmit, isDFAActive, data, input_input_handler];
    }

    class DfaHomePage extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$h, create_fragment$h, safe_not_equal, { data: 3, isDFAActive: 2 });

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "DfaHomePage",
    			options,
    			id: create_fragment$h.name
    		});
    	}

    	get data() {
    		throw new Error("<DfaHomePage>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set data(value) {
    		throw new Error("<DfaHomePage>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	get isDFAActive() {
    		throw new Error("<DfaHomePage>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set isDFAActive(value) {
    		throw new Error("<DfaHomePage>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/shared/connectStatus.svelte generated by Svelte v3.59.1 */

    const { console: console_1$a } = globals;
    const file$g = "src/shared/connectStatus.svelte";

    function create_fragment$g(ctx) {
    	let div;

    	const block = {
    		c: function create() {
    			div = element("div");
    			attr_dev(div, "class", "connectStats svelte-lphwdf");
    			toggle_class(div, "connected", /*userStatus*/ ctx[0] == 1);
    			toggle_class(div, "disconnected", /*userStatus*/ ctx[0] == 0);
    			add_location(div, file$g, 51, 0, 868);
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div, anchor);
    		},
    		p: function update(ctx, [dirty]) {
    			if (dirty & /*userStatus*/ 1) {
    				toggle_class(div, "connected", /*userStatus*/ ctx[0] == 1);
    			}

    			if (dirty & /*userStatus*/ 1) {
    				toggle_class(div, "disconnected", /*userStatus*/ ctx[0] == 0);
    			}
    		},
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$g.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function sleep(ms) {
    	return new Promise(resolve => setTimeout(resolve, ms));
    }

    function instance$g($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('ConnectStatus', slots, []);
    	let { userId } = $$props;

    	// //var
    	// const statusType = {
    	// 	Disconnected: 0,
    	// 	Connected: 1,
    	// 	InGame: 2
    	// }
    	let userStatus = 0;

    	let intervalRefresh;

    	onMount(async () => {
    		await sleep(500); // Pause d'une 1/2 seconde

    		intervalRefresh = setInterval(
    			() => {
    				checkConnexion(userId);
    			},
    			1000
    		);
    	});

    	onDestroy(() => {
    		clearInterval(intervalRefresh);
    	});

    	async function checkConnexion(userId) {
    		try {
    			if (!userId) return;
    			const response = await fetch(`http://${hostname}:3000/chat/connected/${userId}`);
    			let status = await response.json();
    			$$invalidate(0, userStatus = status);
    		} catch(error) {
    			console.error(error);
    		}
    	}

    	$$self.$$.on_mount.push(function () {
    		if (userId === undefined && !('userId' in $$props || $$self.$$.bound[$$self.$$.props['userId']])) {
    			console_1$a.warn("<ConnectStatus> was created without expected prop 'userId'");
    		}
    	});

    	const writable_props = ['userId'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console_1$a.warn(`<ConnectStatus> was created with unknown prop '${key}'`);
    	});

    	$$self.$$set = $$props => {
    		if ('userId' in $$props) $$invalidate(1, userId = $$props.userId);
    	};

    	$$self.$capture_state = () => ({
    		onDestroy,
    		onMount,
    		hostname,
    		userId,
    		userStatus,
    		intervalRefresh,
    		sleep,
    		checkConnexion
    	});

    	$$self.$inject_state = $$props => {
    		if ('userId' in $$props) $$invalidate(1, userId = $$props.userId);
    		if ('userStatus' in $$props) $$invalidate(0, userStatus = $$props.userStatus);
    		if ('intervalRefresh' in $$props) intervalRefresh = $$props.intervalRefresh;
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [userStatus, userId];
    }

    class ConnectStatus extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$g, create_fragment$g, safe_not_equal, { userId: 1 });

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "ConnectStatus",
    			options,
    			id: create_fragment$g.name
    		});
    	}

    	get userId() {
    		throw new Error("<ConnectStatus>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set userId(value) {
    		throw new Error("<ConnectStatus>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/component/Header.svelte generated by Svelte v3.59.1 */
    const file$f = "src/component/Header.svelte";

    function create_fragment$f(ctx) {
    	let header;
    	let div0;
    	let img;
    	let img_src_value;
    	let t0;
    	let div1;
    	let h1;
    	let t2;
    	let p;

    	const block = {
    		c: function create() {
    			header = element("header");
    			div0 = element("div");
    			img = element("img");
    			t0 = space();
    			div1 = element("div");
    			h1 = element("h1");
    			h1.textContent = "FT_TRANSCENDENCE";
    			t2 = space();
    			p = element("p");
    			p.textContent = "A strange adventure into Pong Univers inside an Multiverse inside a jelly jar inside something else and go on ...";
    			if (!src_url_equal(img.src, img_src_value = /*img_path*/ ctx[0])) attr_dev(img, "src", img_src_value);
    			attr_dev(img, "alt", "logo");
    			attr_dev(img, "class", "rick svelte-1rra1ky");
    			add_location(img, file$f, 13, 2, 256);
    			attr_dev(div0, "class", "image-container svelte-1rra1ky");
    			add_location(div0, file$f, 12, 1, 224);
    			attr_dev(h1, "class", "glow-text svelte-1rra1ky");
    			add_location(h1, file$f, 17, 2, 377);
    			attr_dev(p, "class", "catch-phrase svelte-1rra1ky");
    			add_location(p, file$f, 18, 2, 423);
    			attr_dev(div1, "class", "description svelte-1rra1ky");
    			add_location(div1, file$f, 16, 1, 349);
    			attr_dev(header, "class", "svelte-1rra1ky");
    			add_location(header, file$f, 11, 0, 214);
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, header, anchor);
    			append_dev(header, div0);
    			append_dev(div0, img);
    			append_dev(header, t0);
    			append_dev(header, div1);
    			append_dev(div1, h1);
    			append_dev(div1, t2);
    			append_dev(div1, p);
    		},
    		p: function update(ctx, [dirty]) {
    			if (dirty & /*img_path*/ 1 && !src_url_equal(img.src, img_src_value = /*img_path*/ ctx[0])) {
    				attr_dev(img, "src", img_src_value);
    			}
    		},
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(header);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$f.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$f($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Header', slots, []);
    	let { img_path } = $$props;
    	let { data } = $$props;
    	let id = -1;
    	if (data) id = data.id;

    	$$self.$$.on_mount.push(function () {
    		if (img_path === undefined && !('img_path' in $$props || $$self.$$.bound[$$self.$$.props['img_path']])) {
    			console.warn("<Header> was created without expected prop 'img_path'");
    		}

    		if (data === undefined && !('data' in $$props || $$self.$$.bound[$$self.$$.props['data']])) {
    			console.warn("<Header> was created without expected prop 'data'");
    		}
    	});

    	const writable_props = ['img_path', 'data'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console.warn(`<Header> was created with unknown prop '${key}'`);
    	});

    	$$self.$$set = $$props => {
    		if ('img_path' in $$props) $$invalidate(0, img_path = $$props.img_path);
    		if ('data' in $$props) $$invalidate(1, data = $$props.data);
    	};

    	$$self.$capture_state = () => ({
    		dataset_dev,
    		ConnectStatus,
    		img_path,
    		data,
    		id
    	});

    	$$self.$inject_state = $$props => {
    		if ('img_path' in $$props) $$invalidate(0, img_path = $$props.img_path);
    		if ('data' in $$props) $$invalidate(1, data = $$props.data);
    		if ('id' in $$props) id = $$props.id;
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [img_path, data];
    }

    class Header extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$f, create_fragment$f, safe_not_equal, { img_path: 0, data: 1 });

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Header",
    			options,
    			id: create_fragment$f.name
    		});
    	}

    	get img_path() {
    		throw new Error("<Header>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set img_path(value) {
    		throw new Error("<Header>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	get data() {
    		throw new Error("<Header>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set data(value) {
    		throw new Error("<Header>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/component/Footer.svelte generated by Svelte v3.59.1 */

    const file$e = "src/component/Footer.svelte";

    function create_fragment$e(ctx) {
    	let footer;
    	let div;

    	const block = {
    		c: function create() {
    			footer = element("footer");
    			div = element("div");
    			div.textContent = "Transcendental team42 - share like suscribe";
    			attr_dev(div, "class", "bigup svelte-cyutd8");
    			add_location(div, file$e, 1, 1, 10);
    			attr_dev(footer, "class", "svelte-cyutd8");
    			add_location(footer, file$e, 0, 0, 0);
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, footer, anchor);
    			append_dev(footer, div);
    		},
    		p: noop$1,
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(footer);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$e.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$e($$self, $$props) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Footer', slots, []);
    	const writable_props = [];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console.warn(`<Footer> was created with unknown prop '${key}'`);
    	});

    	return [];
    }

    class Footer extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$e, create_fragment$e, safe_not_equal, {});

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Footer",
    			options,
    			id: create_fragment$e.name
    		});
    	}
    }

    /* src/shared/Ranking.svelte generated by Svelte v3.59.1 */

    const { console: console_1$9 } = globals;
    const file$d = "src/shared/Ranking.svelte";

    function get_each_context$5(ctx, list, i) {
    	const child_ctx = ctx.slice();
    	child_ctx[7] = list[i];
    	return child_ctx;
    }

    // (23:0) {#if ranksTab}
    function create_if_block$9(ctx) {
    	let await_block_anchor;

    	let info = {
    		ctx,
    		current: null,
    		token: null,
    		hasCatch: true,
    		pending: create_pending_block$5,
    		then: create_then_block$5,
    		catch: create_catch_block$5,
    		error: 10
    	};

    	handle_promise(/*getClientStatsOrdered*/ ctx[2](), info);

    	const block = {
    		c: function create() {
    			await_block_anchor = empty$1();
    			info.block.c();
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, await_block_anchor, anchor);
    			info.block.m(target, info.anchor = anchor);
    			info.mount = () => await_block_anchor.parentNode;
    			info.anchor = await_block_anchor;
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			update_await_block_branch(info, ctx, dirty);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(await_block_anchor);
    			info.block.d(detaching);
    			info.token = null;
    			info = null;
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block$9.name,
    		type: "if",
    		source: "(23:0) {#if ranksTab}",
    		ctx
    	});

    	return block;
    }

    // (66:1) {:catch error}
    function create_catch_block$5(ctx) {
    	let p;
    	let t0;
    	let t1_value = /*error*/ ctx[10].message + "";
    	let t1;

    	const block = {
    		c: function create() {
    			p = element("p");
    			t0 = text("Une erreur s'est produite : ");
    			t1 = text(t1_value);
    			add_location(p, file$d, 66, 2, 1621);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    			append_dev(p, t0);
    			append_dev(p, t1);
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_catch_block$5.name,
    		type: "catch",
    		source: "(66:1) {:catch error}",
    		ctx
    	});

    	return block;
    }

    // (29:3) {:then}
    function create_then_block$5(ctx) {
    	let div1;
    	let div0;
    	let h1;
    	let t1;
    	let mounted;
    	let dispose;

    	function select_block_type(ctx, dirty) {
    		if (/*classment*/ ctx[1].length !== 0) return create_if_block_1$7;
    		return create_else_block$4;
    	}

    	let current_block_type = select_block_type(ctx);
    	let if_block = current_block_type(ctx);

    	const block = {
    		c: function create() {
    			div1 = element("div");
    			div0 = element("div");
    			h1 = element("h1");
    			h1.textContent = "Ranking";
    			t1 = space();
    			if_block.c();
    			add_location(h1, file$d, 32, 4, 602);
    			attr_dev(div0, "class", "modal svelte-1ilhx9i");
    			add_location(div0, file$d, 31, 3, 578);
    			attr_dev(div1, "class", "backdrop svelte-1ilhx9i");
    			add_location(div1, file$d, 29, 2, 525);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div1, anchor);
    			append_dev(div1, div0);
    			append_dev(div0, h1);
    			append_dev(div0, t1);
    			if_block.m(div0, null);

    			if (!mounted) {
    				dispose = [
    					listen_dev(div1, "click", self$1(/*click_handler_1*/ ctx[5]), false, false, false, false),
    					listen_dev(div1, "keypress", /*keypress_handler_1*/ ctx[6], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (current_block_type === (current_block_type = select_block_type(ctx)) && if_block) {
    				if_block.p(ctx, dirty);
    			} else {
    				if_block.d(1);
    				if_block = current_block_type(ctx);

    				if (if_block) {
    					if_block.c();
    					if_block.m(div0, null);
    				}
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div1);
    			if_block.d();
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_then_block$5.name,
    		type: "then",
    		source: "(29:3) {:then}",
    		ctx
    	});

    	return block;
    }

    // (38:4) {:else}
    function create_else_block$4(ctx) {
    	let p0;
    	let t1;
    	let p1;
    	let t3;
    	let p2;
    	let t5;
    	let p3;
    	let t7;
    	let p4;
    	let t9;
    	let p5;
    	let t11;
    	let p6;
    	let t13;
    	let p7;
    	let t15;

    	const block = {
    		c: function create() {
    			p0 = element("p");
    			p0.textContent = "nobody has played yet";
    			t1 = space();
    			p1 = element("p");
    			p1.textContent = "please stay";
    			t3 = space();
    			p2 = element("p");
    			p2.textContent = "share with your friends";
    			t5 = space();
    			p3 = element("p");
    			p3.textContent = "don't leave";
    			t7 = space();
    			p4 = element("p");
    			p4.textContent = "love us";
    			t9 = space();
    			p5 = element("p");
    			p5.textContent = "give us a chance";
    			t11 = space();
    			p6 = element("p");
    			p6.textContent = "pong is not that bad";
    			t13 = space();
    			p7 = element("p");
    			p7.textContent = "i'll be better i promise...";
    			t15 = text("\n\t\t\t\t\t⠀⠀⠀⠀⠀⠀⠀⠀⢀⠠⠄⠒⠒⠉⠉⠉⠉⠉⠓⠂⠤⢀⠀⠀⠀⠀⠀⠀⠀⠀\n\t\t\t\t\t⠀⠀⠀⠀⠀⢀⠄⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠢⢄⠀⠀⠀⠀⠀\n\t\t\t\t\t⠀⠀⠀⢀⠔⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⠀⠀⠀\n\t\t\t\t\t⠀⠀⡰⠁⠀⠀⠀⠀⠀⣀⣀⣀⡀⠀⠀⠀⠀⠀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠢⠀⠀\n\t\t\t\t\t⠀⡐⠀⠀⠀⢀⣤⣶⣿⣿⣿⣿⣿⣦⠀⠀⣰⣾⣿⣿⣿⣿⣷⣦⣄⠀⠀⠀⠱⠀\n\t\t\t\t\t⡰⠀⠀⢀⣴⣿⠟⠉⢈⠟⠁⢹⣿⣿⡇⢀⣿⠟⠁⠀⡬⠛⣿⣿⣿⣷⣄⠀⠀⢡\n\t\t\t\t\t⡇⠀⣠⣿⡿⠁⠀⠀⢎⠀⢀⣼⣿⣿⡇⢸⠏⠀⠀⠘⠀⣰⣿⣿⣿⣿⣿⣦⠀⢸\n\t\t\t\t\t⡇⢠⠃⡿⠁⠀⠀⠀⠀⣷⣿⣿⣿⣿⡿⢸⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⡆⢧⢸\n\t\t\t\t\t⡇⡞⠀⡇⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⡇⢸⣆⡀⠀⢀⣼⣿⣿⣿⣿⣿⣿⡇⢸⢸\n\t\t\t\t\t⡇⢧⠀⢷⣄⣀⣀⣴⣿⣿⣿⣿⣿⣿⡇⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⢸⢸\n\t\t\t\t\t⢰⠸⡄⠘⣿⡟⠻⣿⣿⣿⣿⣿⣿⡿⠁⠀⢻⣿⡉⠙⣿⣿⣿⣿⣿⣿⡏⠀⡞⡸\n\t\t\t\t\t⠀⢂⠹⣄⠘⣧⣠⣾⣿⡿⢿⣣⡿⠁⠀⠀⠀⠻⣿⣿⢿⡿⢟⣾⣿⠏⢀⠜⠠⠁\n\t\t\t\t\t⠀⠀⠢⡈⠑⠚⠿⠷⠶⠿⠟⠋⠀⠀⠀⠀⠀⠀⠈⠛⠿⠾⠿⠿⠕⠛⠁⡰⠁⠀\n\t\t\t\t\t⠀⠀⠀⠑⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠊⠀⠀⠀\n\t\t\t\t\t⠀⠀⠀⠀⠀⠑⠠⡀⠀⠀⠀⠀⠀⠠⠞⠙⠦⠀⠀⠀⠀⠀⢀⡠⠊⠀⠀⠀⠀⠀\n\t\t\t\t\t⠀⠀⠀⠀⠀⠀⠀⠀⠁⠂⠤⢀⣀⣀⣀⣀⣀⣀⣀⡠⠔⠂⠁⠀⠀⠀⠀⠀⠀⠀");
    			add_location(p0, file$d, 38, 5, 764);
    			add_location(p1, file$d, 39, 5, 798);
    			add_location(p2, file$d, 40, 5, 822);
    			add_location(p3, file$d, 41, 5, 858);
    			add_location(p4, file$d, 42, 5, 882);
    			add_location(p5, file$d, 43, 5, 902);
    			add_location(p6, file$d, 44, 5, 931);
    			add_location(p7, file$d, 45, 5, 964);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p0, anchor);
    			insert_dev(target, t1, anchor);
    			insert_dev(target, p1, anchor);
    			insert_dev(target, t3, anchor);
    			insert_dev(target, p2, anchor);
    			insert_dev(target, t5, anchor);
    			insert_dev(target, p3, anchor);
    			insert_dev(target, t7, anchor);
    			insert_dev(target, p4, anchor);
    			insert_dev(target, t9, anchor);
    			insert_dev(target, p5, anchor);
    			insert_dev(target, t11, anchor);
    			insert_dev(target, p6, anchor);
    			insert_dev(target, t13, anchor);
    			insert_dev(target, p7, anchor);
    			insert_dev(target, t15, anchor);
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p0);
    			if (detaching) detach_dev(t1);
    			if (detaching) detach_dev(p1);
    			if (detaching) detach_dev(t3);
    			if (detaching) detach_dev(p2);
    			if (detaching) detach_dev(t5);
    			if (detaching) detach_dev(p3);
    			if (detaching) detach_dev(t7);
    			if (detaching) detach_dev(p4);
    			if (detaching) detach_dev(t9);
    			if (detaching) detach_dev(p5);
    			if (detaching) detach_dev(t11);
    			if (detaching) detach_dev(p6);
    			if (detaching) detach_dev(t13);
    			if (detaching) detach_dev(p7);
    			if (detaching) detach_dev(t15);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block$4.name,
    		type: "else",
    		source: "(38:4) {:else}",
    		ctx
    	});

    	return block;
    }

    // (34:4) {#if classment.length !== 0}
    function create_if_block_1$7(ctx) {
    	let each_1_anchor;
    	let each_value = /*classment*/ ctx[1];
    	validate_each_argument(each_value);
    	let each_blocks = [];

    	for (let i = 0; i < each_value.length; i += 1) {
    		each_blocks[i] = create_each_block$5(get_each_context$5(ctx, each_value, i));
    	}

    	const block = {
    		c: function create() {
    			for (let i = 0; i < each_blocks.length; i += 1) {
    				each_blocks[i].c();
    			}

    			each_1_anchor = empty$1();
    		},
    		m: function mount(target, anchor) {
    			for (let i = 0; i < each_blocks.length; i += 1) {
    				if (each_blocks[i]) {
    					each_blocks[i].m(target, anchor);
    				}
    			}

    			insert_dev(target, each_1_anchor, anchor);
    		},
    		p: function update(ctx, dirty) {
    			if (dirty & /*JSON, classment*/ 2) {
    				each_value = /*classment*/ ctx[1];
    				validate_each_argument(each_value);
    				let i;

    				for (i = 0; i < each_value.length; i += 1) {
    					const child_ctx = get_each_context$5(ctx, each_value, i);

    					if (each_blocks[i]) {
    						each_blocks[i].p(child_ctx, dirty);
    					} else {
    						each_blocks[i] = create_each_block$5(child_ctx);
    						each_blocks[i].c();
    						each_blocks[i].m(each_1_anchor.parentNode, each_1_anchor);
    					}
    				}

    				for (; i < each_blocks.length; i += 1) {
    					each_blocks[i].d(1);
    				}

    				each_blocks.length = each_value.length;
    			}
    		},
    		d: function destroy(detaching) {
    			destroy_each(each_blocks, detaching);
    			if (detaching) detach_dev(each_1_anchor);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_1$7.name,
    		type: "if",
    		source: "(34:4) {#if classment.length !== 0}",
    		ctx
    	});

    	return block;
    }

    // (35:5) {#each classment as score}
    function create_each_block$5(ctx) {
    	let pre;
    	let t_value = JSON.stringify(/*score*/ ctx[7], null, 0) + "";
    	let t;

    	const block = {
    		c: function create() {
    			pre = element("pre");
    			t = text(t_value);
    			add_location(pre, file$d, 35, 6, 690);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, pre, anchor);
    			append_dev(pre, t);
    		},
    		p: function update(ctx, dirty) {
    			if (dirty & /*classment*/ 2 && t_value !== (t_value = JSON.stringify(/*score*/ ctx[7], null, 0) + "")) set_data_dev(t, t_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(pre);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_each_block$5.name,
    		type: "each",
    		source: "(35:5) {#each classment as score}",
    		ctx
    	});

    	return block;
    }

    // (24:33)     <div class="backdrop" on:click|self on:keypress>    <p>Loading...</p>   </div>    {:then}
    function create_pending_block$5(ctx) {
    	let div;
    	let p;
    	let mounted;
    	let dispose;

    	const block = {
    		c: function create() {
    			div = element("div");
    			p = element("p");
    			p.textContent = "Loading...";
    			add_location(p, file$d, 26, 3, 485);
    			attr_dev(div, "class", "backdrop svelte-1ilhx9i");
    			add_location(div, file$d, 25, 2, 433);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div, anchor);
    			append_dev(div, p);

    			if (!mounted) {
    				dispose = [
    					listen_dev(div, "click", self$1(/*click_handler*/ ctx[3]), false, false, false, false),
    					listen_dev(div, "keypress", /*keypress_handler*/ ctx[4], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_pending_block$5.name,
    		type: "pending",
    		source: "(24:33)     <div class=\\\"backdrop\\\" on:click|self on:keypress>    <p>Loading...</p>   </div>    {:then}",
    		ctx
    	});

    	return block;
    }

    function create_fragment$d(ctx) {
    	let if_block_anchor;
    	let if_block = /*ranksTab*/ ctx[0] && create_if_block$9(ctx);

    	const block = {
    		c: function create() {
    			if (if_block) if_block.c();
    			if_block_anchor = empty$1();
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			if (if_block) if_block.m(target, anchor);
    			insert_dev(target, if_block_anchor, anchor);
    		},
    		p: function update(ctx, [dirty]) {
    			if (/*ranksTab*/ ctx[0]) {
    				if (if_block) {
    					if_block.p(ctx, dirty);
    				} else {
    					if_block = create_if_block$9(ctx);
    					if_block.c();
    					if_block.m(if_block_anchor.parentNode, if_block_anchor);
    				}
    			} else if (if_block) {
    				if_block.d(1);
    				if_block = null;
    			}
    		},
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (if_block) if_block.d(detaching);
    			if (detaching) detach_dev(if_block_anchor);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$d.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$d($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Ranking', slots, []);
    	let { ranksTab } = $$props;
    	let classment = [];

    	async function getClientStatsOrdered() {
    		try {
    			const response = await fetch(`http://${hostname}:3000/dashboard/ranking`);

    			if (response) {
    				$$invalidate(1, classment = await response.json());
    			} else $$invalidate(1, classment = []);
    		} catch(error) {
    			console.error(error);
    		}
    	}

    	$$self.$$.on_mount.push(function () {
    		if (ranksTab === undefined && !('ranksTab' in $$props || $$self.$$.bound[$$self.$$.props['ranksTab']])) {
    			console_1$9.warn("<Ranking> was created without expected prop 'ranksTab'");
    		}
    	});

    	const writable_props = ['ranksTab'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console_1$9.warn(`<Ranking> was created with unknown prop '${key}'`);
    	});

    	function click_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	function keypress_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	function click_handler_1(event) {
    		bubble.call(this, $$self, event);
    	}

    	function keypress_handler_1(event) {
    		bubble.call(this, $$self, event);
    	}

    	$$self.$$set = $$props => {
    		if ('ranksTab' in $$props) $$invalidate(0, ranksTab = $$props.ranksTab);
    	};

    	$$self.$capture_state = () => ({
    		hostname,
    		ranksTab,
    		classment,
    		getClientStatsOrdered
    	});

    	$$self.$inject_state = $$props => {
    		if ('ranksTab' in $$props) $$invalidate(0, ranksTab = $$props.ranksTab);
    		if ('classment' in $$props) $$invalidate(1, classment = $$props.classment);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [
    		ranksTab,
    		classment,
    		getClientStatsOrdered,
    		click_handler,
    		keypress_handler,
    		click_handler_1,
    		keypress_handler_1
    	];
    }

    class Ranking extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$d, create_fragment$d, safe_not_equal, { ranksTab: 0 });

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Ranking",
    			options,
    			id: create_fragment$d.name
    		});
    	}

    	get ranksTab() {
    		throw new Error("<Ranking>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set ranksTab(value) {
    		throw new Error("<Ranking>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/shared/FriendList.svelte generated by Svelte v3.59.1 */

    const { console: console_1$8 } = globals;
    const file$c = "src/shared/FriendList.svelte";

    function get_each_context$4(ctx, list, i) {
    	const child_ctx = ctx.slice();
    	child_ctx[14] = list[i];
    	return child_ctx;
    }

    // (76:0) {#if flTab}
    function create_if_block$8(ctx) {
    	let await_block_anchor;

    	let info = {
    		ctx,
    		current: null,
    		token: null,
    		hasCatch: true,
    		pending: create_pending_block$4,
    		then: create_then_block$4,
    		catch: create_catch_block$4,
    		error: 17
    	};

    	handle_promise(/*getFlforId*/ ctx[2](), info);

    	const block = {
    		c: function create() {
    			await_block_anchor = empty$1();
    			info.block.c();
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, await_block_anchor, anchor);
    			info.block.m(target, info.anchor = anchor);
    			info.mount = () => await_block_anchor.parentNode;
    			info.anchor = await_block_anchor;
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			update_await_block_branch(info, ctx, dirty);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(await_block_anchor);
    			info.block.d(detaching);
    			info.token = null;
    			info = null;
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block$8.name,
    		type: "if",
    		source: "(76:0) {#if flTab}",
    		ctx
    	});

    	return block;
    }

    // (103:1) {:catch error}
    function create_catch_block$4(ctx) {
    	let p;
    	let t0;
    	let t1_value = /*error*/ ctx[17].message + "";
    	let t1;

    	const block = {
    		c: function create() {
    			p = element("p");
    			t0 = text("Une erreur s'est produite: ");
    			t1 = text(t1_value);
    			add_location(p, file$c, 103, 2, 2307);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    			append_dev(p, t0);
    			append_dev(p, t1);
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_catch_block$4.name,
    		type: "catch",
    		source: "(103:1) {:catch error}",
    		ctx
    	});

    	return block;
    }

    // (81:3) {:then}
    function create_then_block$4(ctx) {
    	let div1;
    	let div0;
    	let h1;
    	let t1;
    	let mounted;
    	let dispose;

    	function select_block_type(ctx, dirty) {
    		if (/*fl*/ ctx[1].length !== 0) return create_if_block_1$6;
    		return create_else_block_1$3;
    	}

    	let current_block_type = select_block_type(ctx);
    	let if_block = current_block_type(ctx);

    	const block = {
    		c: function create() {
    			div1 = element("div");
    			div0 = element("div");
    			h1 = element("h1");
    			h1.textContent = "My Friends";
    			t1 = space();
    			if_block.c();
    			add_location(h1, file$c, 84, 5, 1756);
    			attr_dev(div0, "class", "modal svelte-1ilhx9i");
    			add_location(div0, file$c, 83, 4, 1731);
    			attr_dev(div1, "class", "backdrop svelte-1ilhx9i");
    			add_location(div1, file$c, 82, 2, 1678);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div1, anchor);
    			append_dev(div1, div0);
    			append_dev(div0, h1);
    			append_dev(div0, t1);
    			if_block.m(div0, null);

    			if (!mounted) {
    				dispose = [
    					listen_dev(div1, "click", self$1(/*click_handler_1*/ ctx[5]), false, false, false, false),
    					listen_dev(div1, "keypress", /*keypress_handler*/ ctx[6], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (current_block_type === (current_block_type = select_block_type(ctx)) && if_block) {
    				if_block.p(ctx, dirty);
    			} else {
    				if_block.d(1);
    				if_block = current_block_type(ctx);

    				if (if_block) {
    					if_block.c();
    					if_block.m(div0, null);
    				}
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div1);
    			if_block.d();
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_then_block$4.name,
    		type: "then",
    		source: "(81:3) {:then}",
    		ctx
    	});

    	return block;
    }

    // (95:5) {:else}
    function create_else_block_1$3(ctx) {
    	let h1;
    	let t1;
    	let p0;
    	let t3;
    	let p1;

    	const block = {
    		c: function create() {
    			h1 = element("h1");
    			h1.textContent = "┌∩┐(◕_◕)┌∩┐";
    			t1 = space();
    			p0 = element("p");
    			p0.textContent = "No friend";
    			t3 = space();
    			p1 = element("p");
    			p1.textContent = "nobody loves you...";
    			add_location(h1, file$c, 95, 6, 2093);
    			add_location(p0, file$c, 96, 6, 2120);
    			add_location(p1, file$c, 97, 6, 2143);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, h1, anchor);
    			insert_dev(target, t1, anchor);
    			insert_dev(target, p0, anchor);
    			insert_dev(target, t3, anchor);
    			insert_dev(target, p1, anchor);
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(h1);
    			if (detaching) detach_dev(t1);
    			if (detaching) detach_dev(p0);
    			if (detaching) detach_dev(t3);
    			if (detaching) detach_dev(p1);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block_1$3.name,
    		type: "else",
    		source: "(95:5) {:else}",
    		ctx
    	});

    	return block;
    }

    // (87:5) {#if fl.length !== 0}
    function create_if_block_1$6(ctx) {
    	let each_1_anchor;
    	let each_value = /*fl*/ ctx[1];
    	validate_each_argument(each_value);
    	let each_blocks = [];

    	for (let i = 0; i < each_value.length; i += 1) {
    		each_blocks[i] = create_each_block$4(get_each_context$4(ctx, each_value, i));
    	}

    	const block = {
    		c: function create() {
    			for (let i = 0; i < each_blocks.length; i += 1) {
    				each_blocks[i].c();
    			}

    			each_1_anchor = empty$1();
    		},
    		m: function mount(target, anchor) {
    			for (let i = 0; i < each_blocks.length; i += 1) {
    				if (each_blocks[i]) {
    					each_blocks[i].m(target, anchor);
    				}
    			}

    			insert_dev(target, each_1_anchor, anchor);
    		},
    		p: function update(ctx, dirty) {
    			if (dirty & /*fl*/ 2) {
    				each_value = /*fl*/ ctx[1];
    				validate_each_argument(each_value);
    				let i;

    				for (i = 0; i < each_value.length; i += 1) {
    					const child_ctx = get_each_context$4(ctx, each_value, i);

    					if (each_blocks[i]) {
    						each_blocks[i].p(child_ctx, dirty);
    					} else {
    						each_blocks[i] = create_each_block$4(child_ctx);
    						each_blocks[i].c();
    						each_blocks[i].m(each_1_anchor.parentNode, each_1_anchor);
    					}
    				}

    				for (; i < each_blocks.length; i += 1) {
    					each_blocks[i].d(1);
    				}

    				each_blocks.length = each_value.length;
    			}
    		},
    		d: function destroy(detaching) {
    			destroy_each(each_blocks, detaching);
    			if (detaching) detach_dev(each_1_anchor);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_1$6.name,
    		type: "if",
    		source: "(87:5) {#if fl.length !== 0}",
    		ctx
    	});

    	return block;
    }

    // (91:7) {:else}
    function create_else_block$3(ctx) {
    	let h3;
    	let t0_value = /*friend*/ ctx[14].client.name + "";
    	let t0;
    	let t1;

    	const block = {
    		c: function create() {
    			h3 = element("h3");
    			t0 = text(t0_value);
    			t1 = text(" ⛔️ ");
    			add_location(h3, file$c, 91, 8, 2012);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, h3, anchor);
    			append_dev(h3, t0);
    			append_dev(h3, t1);
    		},
    		p: function update(ctx, dirty) {
    			if (dirty & /*fl*/ 2 && t0_value !== (t0_value = /*friend*/ ctx[14].client.name + "")) set_data_dev(t0, t0_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(h3);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block$3.name,
    		type: "else",
    		source: "(91:7) {:else}",
    		ctx
    	});

    	return block;
    }

    // (89:7) {#if friend.status == 0}
    function create_if_block_2$5(ctx) {
    	let h3;
    	let t0_value = /*friend*/ ctx[14].client.name + "";
    	let t0;
    	let t1;

    	const block = {
    		c: function create() {
    			h3 = element("h3");
    			t0 = text(t0_value);
    			t1 = space();
    			add_location(h3, file$c, 89, 8, 1957);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, h3, anchor);
    			append_dev(h3, t0);
    			append_dev(h3, t1);
    		},
    		p: function update(ctx, dirty) {
    			if (dirty & /*fl*/ 2 && t0_value !== (t0_value = /*friend*/ ctx[14].client.name + "")) set_data_dev(t0, t0_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(h3);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_2$5.name,
    		type: "if",
    		source: "(89:7) {#if friend.status == 0}",
    		ctx
    	});

    	return block;
    }

    // (88:6) {#each fl as friend}
    function create_each_block$4(ctx) {
    	let if_block_anchor;

    	function select_block_type_1(ctx, dirty) {
    		if (/*friend*/ ctx[14].status == 0) return create_if_block_2$5;
    		return create_else_block$3;
    	}

    	let current_block_type = select_block_type_1(ctx);
    	let if_block = current_block_type(ctx);

    	const block = {
    		c: function create() {
    			if_block.c();
    			if_block_anchor = empty$1();
    		},
    		m: function mount(target, anchor) {
    			if_block.m(target, anchor);
    			insert_dev(target, if_block_anchor, anchor);
    		},
    		p: function update(ctx, dirty) {
    			if (current_block_type === (current_block_type = select_block_type_1(ctx)) && if_block) {
    				if_block.p(ctx, dirty);
    			} else {
    				if_block.d(1);
    				if_block = current_block_type(ctx);

    				if (if_block) {
    					if_block.c();
    					if_block.m(if_block_anchor.parentNode, if_block_anchor);
    				}
    			}
    		},
    		d: function destroy(detaching) {
    			if_block.d(detaching);
    			if (detaching) detach_dev(if_block_anchor);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_each_block$4.name,
    		type: "each",
    		source: "(88:6) {#each fl as friend}",
    		ctx
    	});

    	return block;
    }

    // (77:22)    <div class="backdrop" on:click|self on:keypress={() => getFlforId()}
    function create_pending_block$4(ctx) {
    	let div;
    	let p;
    	let mounted;
    	let dispose;

    	const block = {
    		c: function create() {
    			div = element("div");
    			p = element("p");
    			p.textContent = "Loading...";
    			add_location(p, file$c, 78, 3, 1552);
    			attr_dev(div, "class", "backdrop svelte-1ilhx9i");
    			add_location(div, file$c, 77, 2, 1479);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div, anchor);
    			append_dev(div, p);

    			if (!mounted) {
    				dispose = [
    					listen_dev(div, "click", self$1(/*click_handler*/ ctx[4]), false, false, false, false),
    					listen_dev(div, "keypress", /*keypress_handler_1*/ ctx[7], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_pending_block$4.name,
    		type: "pending",
    		source: "(77:22)    <div class=\\\"backdrop\\\" on:click|self on:keypress={() => getFlforId()}",
    		ctx
    	});

    	return block;
    }

    function create_fragment$c(ctx) {
    	let if_block_anchor;
    	let if_block = /*flTab*/ ctx[0] && create_if_block$8(ctx);

    	const block = {
    		c: function create() {
    			if (if_block) if_block.c();
    			if_block_anchor = empty$1();
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			if (if_block) if_block.m(target, anchor);
    			insert_dev(target, if_block_anchor, anchor);
    		},
    		p: function update(ctx, [dirty]) {
    			if (/*flTab*/ ctx[0]) {
    				if (if_block) {
    					if_block.p(ctx, dirty);
    				} else {
    					if_block = create_if_block$8(ctx);
    					if_block.c();
    					if_block.m(if_block_anchor.parentNode, if_block_anchor);
    				}
    			} else if (if_block) {
    				if_block.d(1);
    				if_block = null;
    			}
    		},
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (if_block) if_block.d(detaching);
    			if (detaching) detach_dev(if_block_anchor);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$c.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    async function blockTarget() {
    	
    }

    function instance$c($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('FriendList', slots, []);
    	const dispatch = createEventDispatcher();
    	let { flTab } = $$props;
    	let { id } = $$props;
    	let fl = [];
    	let id42NameInputNotEmpty = false;
    	let searchRes = [];

    	async function getFlforId() {
    		try {
    			const response = await fetch(`http://${hostname}:3000/dashboard/fl/${id}`);

    			if (response) {
    				$$invalidate(1, fl = await response.json());
    			} else $$invalidate(1, fl = []);
    		} catch(error) {
    			console.error(error);
    		}
    	}

    	async function getSpecifiedClients() {
    		const retName = document.getElementById('id42-name-input').value;
    		id42NameInputNotEmpty = retName.trim() !== '';

    		if (id42NameInputNotEmpty) {
    			try {
    				const response = await fetch(`http://${hostname}:3000/dashboard/name/${retName}`);
    				searchRes = await response.json();
    			} catch(error) {
    				console.error(error);
    			}
    		} else searchRes = [];

    		$$invalidate(1, fl = searchRes);
    	}

    	async function addFl() {
    		const response = await fetch(`http://${hostname}:3000/dashboard/fl/${id}`);

    		if (response.ok) {
    			rooms = await response.json();
    		} else {
    			console.error('Failed to fetch friend list');
    		}
    	}

    	async function inspectTarget() {
    		document.getElementById('id42-name-input').value;
    		searchRes = [];
    		$$invalidate(1, fl = []);
    		id42NameInputNotEmpty = false;
    	}

    	$$self.$$.on_mount.push(function () {
    		if (flTab === undefined && !('flTab' in $$props || $$self.$$.bound[$$self.$$.props['flTab']])) {
    			console_1$8.warn("<FriendList> was created without expected prop 'flTab'");
    		}

    		if (id === undefined && !('id' in $$props || $$self.$$.bound[$$self.$$.props['id']])) {
    			console_1$8.warn("<FriendList> was created without expected prop 'id'");
    		}
    	});

    	const writable_props = ['flTab', 'id'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console_1$8.warn(`<FriendList> was created with unknown prop '${key}'`);
    	});

    	function click_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	function click_handler_1(event) {
    		bubble.call(this, $$self, event);
    	}

    	function keypress_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	const keypress_handler_1 = () => getFlforId();

    	$$self.$$set = $$props => {
    		if ('flTab' in $$props) $$invalidate(0, flTab = $$props.flTab);
    		if ('id' in $$props) $$invalidate(3, id = $$props.id);
    	};

    	$$self.$capture_state = () => ({
    		add_flush_callback,
    		createEventDispatcher,
    		hostname,
    		dispatch,
    		flTab,
    		id,
    		fl,
    		id42NameInputNotEmpty,
    		searchRes,
    		getFlforId,
    		getSpecifiedClients,
    		addFl,
    		blockTarget,
    		inspectTarget
    	});

    	$$self.$inject_state = $$props => {
    		if ('flTab' in $$props) $$invalidate(0, flTab = $$props.flTab);
    		if ('id' in $$props) $$invalidate(3, id = $$props.id);
    		if ('fl' in $$props) $$invalidate(1, fl = $$props.fl);
    		if ('id42NameInputNotEmpty' in $$props) id42NameInputNotEmpty = $$props.id42NameInputNotEmpty;
    		if ('searchRes' in $$props) searchRes = $$props.searchRes;
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [
    		flTab,
    		fl,
    		getFlforId,
    		id,
    		click_handler,
    		click_handler_1,
    		keypress_handler,
    		keypress_handler_1
    	];
    }

    class FriendList extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$c, create_fragment$c, safe_not_equal, { flTab: 0, id: 3 });

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "FriendList",
    			options,
    			id: create_fragment$c.name
    		});
    	}

    	get flTab() {
    		throw new Error("<FriendList>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set flTab(value) {
    		throw new Error("<FriendList>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	get id() {
    		throw new Error("<FriendList>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set id(value) {
    		throw new Error("<FriendList>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    const subscriber_queue = [];
    /**
     * Create a `Writable` store that allows both updating and reading by subscription.
     * @param {*=}value initial value
     * @param {StartStopNotifier=} start
     */
    function writable(value, start = noop$1) {
        let stop;
        const subscribers = new Set();
        function set(new_value) {
            if (safe_not_equal(value, new_value)) {
                value = new_value;
                if (stop) { // store is ready
                    const run_queue = !subscriber_queue.length;
                    for (const subscriber of subscribers) {
                        subscriber[1]();
                        subscriber_queue.push(subscriber, value);
                    }
                    if (run_queue) {
                        for (let i = 0; i < subscriber_queue.length; i += 2) {
                            subscriber_queue[i][0](subscriber_queue[i + 1]);
                        }
                        subscriber_queue.length = 0;
                    }
                }
            }
        }
        function update(fn) {
            set(fn(value));
        }
        function subscribe(run, invalidate = noop$1) {
            const subscriber = [run, invalidate];
            subscribers.add(subscriber);
            if (subscribers.size === 1) {
                stop = start(set) || noop$1;
            }
            run(value);
            return () => {
                subscribers.delete(subscriber);
                if (subscribers.size === 0 && stop) {
                    stop();
                    stop = null;
                }
            };
        }
        return { set, update, subscribe };
    }

    const id42 = document.cookie ? document.cookie
        .split('; ')
        .find(cookie => cookie.startsWith('id42'))
        .split('=')[1] : null;

    const userId42 = writable(id42);
    let page_shown = writable("/");

    const PACKET_TYPES = Object.create(null); // no Map = no polyfill
    PACKET_TYPES["open"] = "0";
    PACKET_TYPES["close"] = "1";
    PACKET_TYPES["ping"] = "2";
    PACKET_TYPES["pong"] = "3";
    PACKET_TYPES["message"] = "4";
    PACKET_TYPES["upgrade"] = "5";
    PACKET_TYPES["noop"] = "6";
    const PACKET_TYPES_REVERSE = Object.create(null);
    Object.keys(PACKET_TYPES).forEach(key => {
        PACKET_TYPES_REVERSE[PACKET_TYPES[key]] = key;
    });
    const ERROR_PACKET = { type: "error", data: "parser error" };

    const withNativeBlob$1 = typeof Blob === "function" ||
        (typeof Blob !== "undefined" &&
            Object.prototype.toString.call(Blob) === "[object BlobConstructor]");
    const withNativeArrayBuffer$2 = typeof ArrayBuffer === "function";
    // ArrayBuffer.isView method is not defined in IE10
    const isView$1 = obj => {
        return typeof ArrayBuffer.isView === "function"
            ? ArrayBuffer.isView(obj)
            : obj && obj.buffer instanceof ArrayBuffer;
    };
    const encodePacket = ({ type, data }, supportsBinary, callback) => {
        if (withNativeBlob$1 && data instanceof Blob) {
            if (supportsBinary) {
                return callback(data);
            }
            else {
                return encodeBlobAsBase64(data, callback);
            }
        }
        else if (withNativeArrayBuffer$2 &&
            (data instanceof ArrayBuffer || isView$1(data))) {
            if (supportsBinary) {
                return callback(data);
            }
            else {
                return encodeBlobAsBase64(new Blob([data]), callback);
            }
        }
        // plain string
        return callback(PACKET_TYPES[type] + (data || ""));
    };
    const encodeBlobAsBase64 = (data, callback) => {
        const fileReader = new FileReader();
        fileReader.onload = function () {
            const content = fileReader.result.split(",")[1];
            callback("b" + (content || ""));
        };
        return fileReader.readAsDataURL(data);
    };

    // imported from https://github.com/socketio/base64-arraybuffer
    const chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/';
    // Use a lookup table to find the index.
    const lookup$1 = typeof Uint8Array === 'undefined' ? [] : new Uint8Array(256);
    for (let i = 0; i < chars.length; i++) {
        lookup$1[chars.charCodeAt(i)] = i;
    }
    const decode$1 = (base64) => {
        let bufferLength = base64.length * 0.75, len = base64.length, i, p = 0, encoded1, encoded2, encoded3, encoded4;
        if (base64[base64.length - 1] === '=') {
            bufferLength--;
            if (base64[base64.length - 2] === '=') {
                bufferLength--;
            }
        }
        const arraybuffer = new ArrayBuffer(bufferLength), bytes = new Uint8Array(arraybuffer);
        for (i = 0; i < len; i += 4) {
            encoded1 = lookup$1[base64.charCodeAt(i)];
            encoded2 = lookup$1[base64.charCodeAt(i + 1)];
            encoded3 = lookup$1[base64.charCodeAt(i + 2)];
            encoded4 = lookup$1[base64.charCodeAt(i + 3)];
            bytes[p++] = (encoded1 << 2) | (encoded2 >> 4);
            bytes[p++] = ((encoded2 & 15) << 4) | (encoded3 >> 2);
            bytes[p++] = ((encoded3 & 3) << 6) | (encoded4 & 63);
        }
        return arraybuffer;
    };

    const withNativeArrayBuffer$1 = typeof ArrayBuffer === "function";
    const decodePacket = (encodedPacket, binaryType) => {
        if (typeof encodedPacket !== "string") {
            return {
                type: "message",
                data: mapBinary(encodedPacket, binaryType)
            };
        }
        const type = encodedPacket.charAt(0);
        if (type === "b") {
            return {
                type: "message",
                data: decodeBase64Packet(encodedPacket.substring(1), binaryType)
            };
        }
        const packetType = PACKET_TYPES_REVERSE[type];
        if (!packetType) {
            return ERROR_PACKET;
        }
        return encodedPacket.length > 1
            ? {
                type: PACKET_TYPES_REVERSE[type],
                data: encodedPacket.substring(1)
            }
            : {
                type: PACKET_TYPES_REVERSE[type]
            };
    };
    const decodeBase64Packet = (data, binaryType) => {
        if (withNativeArrayBuffer$1) {
            const decoded = decode$1(data);
            return mapBinary(decoded, binaryType);
        }
        else {
            return { base64: true, data }; // fallback for old browsers
        }
    };
    const mapBinary = (data, binaryType) => {
        switch (binaryType) {
            case "blob":
                return data instanceof ArrayBuffer ? new Blob([data]) : data;
            case "arraybuffer":
            default:
                return data; // assuming the data is already an ArrayBuffer
        }
    };

    const SEPARATOR = String.fromCharCode(30); // see https://en.wikipedia.org/wiki/Delimiter#ASCII_delimited_text
    const encodePayload = (packets, callback) => {
        // some packets may be added to the array while encoding, so the initial length must be saved
        const length = packets.length;
        const encodedPackets = new Array(length);
        let count = 0;
        packets.forEach((packet, i) => {
            // force base64 encoding for binary packets
            encodePacket(packet, false, encodedPacket => {
                encodedPackets[i] = encodedPacket;
                if (++count === length) {
                    callback(encodedPackets.join(SEPARATOR));
                }
            });
        });
    };
    const decodePayload = (encodedPayload, binaryType) => {
        const encodedPackets = encodedPayload.split(SEPARATOR);
        const packets = [];
        for (let i = 0; i < encodedPackets.length; i++) {
            const decodedPacket = decodePacket(encodedPackets[i], binaryType);
            packets.push(decodedPacket);
            if (decodedPacket.type === "error") {
                break;
            }
        }
        return packets;
    };
    const protocol$1 = 4;

    /**
     * Initialize a new `Emitter`.
     *
     * @api public
     */

    function Emitter(obj) {
      if (obj) return mixin(obj);
    }

    /**
     * Mixin the emitter properties.
     *
     * @param {Object} obj
     * @return {Object}
     * @api private
     */

    function mixin(obj) {
      for (var key in Emitter.prototype) {
        obj[key] = Emitter.prototype[key];
      }
      return obj;
    }

    /**
     * Listen on the given `event` with `fn`.
     *
     * @param {String} event
     * @param {Function} fn
     * @return {Emitter}
     * @api public
     */

    Emitter.prototype.on =
    Emitter.prototype.addEventListener = function(event, fn){
      this._callbacks = this._callbacks || {};
      (this._callbacks['$' + event] = this._callbacks['$' + event] || [])
        .push(fn);
      return this;
    };

    /**
     * Adds an `event` listener that will be invoked a single
     * time then automatically removed.
     *
     * @param {String} event
     * @param {Function} fn
     * @return {Emitter}
     * @api public
     */

    Emitter.prototype.once = function(event, fn){
      function on() {
        this.off(event, on);
        fn.apply(this, arguments);
      }

      on.fn = fn;
      this.on(event, on);
      return this;
    };

    /**
     * Remove the given callback for `event` or all
     * registered callbacks.
     *
     * @param {String} event
     * @param {Function} fn
     * @return {Emitter}
     * @api public
     */

    Emitter.prototype.off =
    Emitter.prototype.removeListener =
    Emitter.prototype.removeAllListeners =
    Emitter.prototype.removeEventListener = function(event, fn){
      this._callbacks = this._callbacks || {};

      // all
      if (0 == arguments.length) {
        this._callbacks = {};
        return this;
      }

      // specific event
      var callbacks = this._callbacks['$' + event];
      if (!callbacks) return this;

      // remove all handlers
      if (1 == arguments.length) {
        delete this._callbacks['$' + event];
        return this;
      }

      // remove specific handler
      var cb;
      for (var i = 0; i < callbacks.length; i++) {
        cb = callbacks[i];
        if (cb === fn || cb.fn === fn) {
          callbacks.splice(i, 1);
          break;
        }
      }

      // Remove event specific arrays for event types that no
      // one is subscribed for to avoid memory leak.
      if (callbacks.length === 0) {
        delete this._callbacks['$' + event];
      }

      return this;
    };

    /**
     * Emit `event` with the given args.
     *
     * @param {String} event
     * @param {Mixed} ...
     * @return {Emitter}
     */

    Emitter.prototype.emit = function(event){
      this._callbacks = this._callbacks || {};

      var args = new Array(arguments.length - 1)
        , callbacks = this._callbacks['$' + event];

      for (var i = 1; i < arguments.length; i++) {
        args[i - 1] = arguments[i];
      }

      if (callbacks) {
        callbacks = callbacks.slice(0);
        for (var i = 0, len = callbacks.length; i < len; ++i) {
          callbacks[i].apply(this, args);
        }
      }

      return this;
    };

    // alias used for reserved events (protected method)
    Emitter.prototype.emitReserved = Emitter.prototype.emit;

    /**
     * Return array of callbacks for `event`.
     *
     * @param {String} event
     * @return {Array}
     * @api public
     */

    Emitter.prototype.listeners = function(event){
      this._callbacks = this._callbacks || {};
      return this._callbacks['$' + event] || [];
    };

    /**
     * Check if this emitter has `event` handlers.
     *
     * @param {String} event
     * @return {Boolean}
     * @api public
     */

    Emitter.prototype.hasListeners = function(event){
      return !! this.listeners(event).length;
    };

    const globalThisShim = (() => {
        if (typeof self !== "undefined") {
            return self;
        }
        else if (typeof window !== "undefined") {
            return window;
        }
        else {
            return Function("return this")();
        }
    })();

    function pick(obj, ...attr) {
        return attr.reduce((acc, k) => {
            if (obj.hasOwnProperty(k)) {
                acc[k] = obj[k];
            }
            return acc;
        }, {});
    }
    // Keep a reference to the real timeout functions so they can be used when overridden
    const NATIVE_SET_TIMEOUT = globalThisShim.setTimeout;
    const NATIVE_CLEAR_TIMEOUT = globalThisShim.clearTimeout;
    function installTimerFunctions(obj, opts) {
        if (opts.useNativeTimers) {
            obj.setTimeoutFn = NATIVE_SET_TIMEOUT.bind(globalThisShim);
            obj.clearTimeoutFn = NATIVE_CLEAR_TIMEOUT.bind(globalThisShim);
        }
        else {
            obj.setTimeoutFn = globalThisShim.setTimeout.bind(globalThisShim);
            obj.clearTimeoutFn = globalThisShim.clearTimeout.bind(globalThisShim);
        }
    }
    // base64 encoded buffers are about 33% bigger (https://en.wikipedia.org/wiki/Base64)
    const BASE64_OVERHEAD = 1.33;
    // we could also have used `new Blob([obj]).size`, but it isn't supported in IE9
    function byteLength(obj) {
        if (typeof obj === "string") {
            return utf8Length(obj);
        }
        // arraybuffer or blob
        return Math.ceil((obj.byteLength || obj.size) * BASE64_OVERHEAD);
    }
    function utf8Length(str) {
        let c = 0, length = 0;
        for (let i = 0, l = str.length; i < l; i++) {
            c = str.charCodeAt(i);
            if (c < 0x80) {
                length += 1;
            }
            else if (c < 0x800) {
                length += 2;
            }
            else if (c < 0xd800 || c >= 0xe000) {
                length += 3;
            }
            else {
                i++;
                length += 4;
            }
        }
        return length;
    }

    class TransportError extends Error {
        constructor(reason, description, context) {
            super(reason);
            this.description = description;
            this.context = context;
            this.type = "TransportError";
        }
    }
    class Transport extends Emitter {
        /**
         * Transport abstract constructor.
         *
         * @param {Object} opts - options
         * @protected
         */
        constructor(opts) {
            super();
            this.writable = false;
            installTimerFunctions(this, opts);
            this.opts = opts;
            this.query = opts.query;
            this.socket = opts.socket;
        }
        /**
         * Emits an error.
         *
         * @param {String} reason
         * @param description
         * @param context - the error context
         * @return {Transport} for chaining
         * @protected
         */
        onError(reason, description, context) {
            super.emitReserved("error", new TransportError(reason, description, context));
            return this;
        }
        /**
         * Opens the transport.
         */
        open() {
            this.readyState = "opening";
            this.doOpen();
            return this;
        }
        /**
         * Closes the transport.
         */
        close() {
            if (this.readyState === "opening" || this.readyState === "open") {
                this.doClose();
                this.onClose();
            }
            return this;
        }
        /**
         * Sends multiple packets.
         *
         * @param {Array} packets
         */
        send(packets) {
            if (this.readyState === "open") {
                this.write(packets);
            }
        }
        /**
         * Called upon open
         *
         * @protected
         */
        onOpen() {
            this.readyState = "open";
            this.writable = true;
            super.emitReserved("open");
        }
        /**
         * Called with data.
         *
         * @param {String} data
         * @protected
         */
        onData(data) {
            const packet = decodePacket(data, this.socket.binaryType);
            this.onPacket(packet);
        }
        /**
         * Called with a decoded packet.
         *
         * @protected
         */
        onPacket(packet) {
            super.emitReserved("packet", packet);
        }
        /**
         * Called upon close.
         *
         * @protected
         */
        onClose(details) {
            this.readyState = "closed";
            super.emitReserved("close", details);
        }
        /**
         * Pauses the transport, in order not to lose packets during an upgrade.
         *
         * @param onPause
         */
        pause(onPause) { }
    }

    // imported from https://github.com/unshiftio/yeast
    const alphabet = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_'.split(''), length = 64, map = {};
    let seed = 0, i = 0, prev;
    /**
     * Return a string representing the specified number.
     *
     * @param {Number} num The number to convert.
     * @returns {String} The string representation of the number.
     * @api public
     */
    function encode$3(num) {
        let encoded = '';
        do {
            encoded = alphabet[num % length] + encoded;
            num = Math.floor(num / length);
        } while (num > 0);
        return encoded;
    }
    /**
     * Yeast: A tiny growing id generator.
     *
     * @returns {String} A unique id.
     * @api public
     */
    function yeast() {
        const now = encode$3(+new Date());
        if (now !== prev)
            return seed = 0, prev = now;
        return now + '.' + encode$3(seed++);
    }
    //
    // Map each character to its index.
    //
    for (; i < length; i++)
        map[alphabet[i]] = i;

    // imported from https://github.com/galkn/querystring
    /**
     * Compiles a querystring
     * Returns string representation of the object
     *
     * @param {Object}
     * @api private
     */
    function encode$2(obj) {
        let str = '';
        for (let i in obj) {
            if (obj.hasOwnProperty(i)) {
                if (str.length)
                    str += '&';
                str += encodeURIComponent(i) + '=' + encodeURIComponent(obj[i]);
            }
        }
        return str;
    }
    /**
     * Parses a simple querystring into an object
     *
     * @param {String} qs
     * @api private
     */
    function decode(qs) {
        let qry = {};
        let pairs = qs.split('&');
        for (let i = 0, l = pairs.length; i < l; i++) {
            let pair = pairs[i].split('=');
            qry[decodeURIComponent(pair[0])] = decodeURIComponent(pair[1]);
        }
        return qry;
    }

    // imported from https://github.com/component/has-cors
    let value = false;
    try {
        value = typeof XMLHttpRequest !== 'undefined' &&
            'withCredentials' in new XMLHttpRequest();
    }
    catch (err) {
        // if XMLHttp support is disabled in IE then it will throw
        // when trying to create
    }
    const hasCORS = value;

    // browser shim for xmlhttprequest module
    function XHR(opts) {
        const xdomain = opts.xdomain;
        // XMLHttpRequest can be disabled on IE
        try {
            if ("undefined" !== typeof XMLHttpRequest && (!xdomain || hasCORS)) {
                return new XMLHttpRequest();
            }
        }
        catch (e) { }
        if (!xdomain) {
            try {
                return new globalThisShim[["Active"].concat("Object").join("X")]("Microsoft.XMLHTTP");
            }
            catch (e) { }
        }
    }

    function empty() { }
    const hasXHR2 = (function () {
        const xhr = new XHR({
            xdomain: false,
        });
        return null != xhr.responseType;
    })();
    class Polling extends Transport {
        /**
         * XHR Polling constructor.
         *
         * @param {Object} opts
         * @package
         */
        constructor(opts) {
            super(opts);
            this.polling = false;
            if (typeof location !== "undefined") {
                const isSSL = "https:" === location.protocol;
                let port = location.port;
                // some user agents have empty `location.port`
                if (!port) {
                    port = isSSL ? "443" : "80";
                }
                this.xd =
                    (typeof location !== "undefined" &&
                        opts.hostname !== location.hostname) ||
                        port !== opts.port;
                this.xs = opts.secure !== isSSL;
            }
            /**
             * XHR supports binary
             */
            const forceBase64 = opts && opts.forceBase64;
            this.supportsBinary = hasXHR2 && !forceBase64;
        }
        get name() {
            return "polling";
        }
        /**
         * Opens the socket (triggers polling). We write a PING message to determine
         * when the transport is open.
         *
         * @protected
         */
        doOpen() {
            this.poll();
        }
        /**
         * Pauses polling.
         *
         * @param {Function} onPause - callback upon buffers are flushed and transport is paused
         * @package
         */
        pause(onPause) {
            this.readyState = "pausing";
            const pause = () => {
                this.readyState = "paused";
                onPause();
            };
            if (this.polling || !this.writable) {
                let total = 0;
                if (this.polling) {
                    total++;
                    this.once("pollComplete", function () {
                        --total || pause();
                    });
                }
                if (!this.writable) {
                    total++;
                    this.once("drain", function () {
                        --total || pause();
                    });
                }
            }
            else {
                pause();
            }
        }
        /**
         * Starts polling cycle.
         *
         * @private
         */
        poll() {
            this.polling = true;
            this.doPoll();
            this.emitReserved("poll");
        }
        /**
         * Overloads onData to detect payloads.
         *
         * @protected
         */
        onData(data) {
            const callback = (packet) => {
                // if its the first message we consider the transport open
                if ("opening" === this.readyState && packet.type === "open") {
                    this.onOpen();
                }
                // if its a close packet, we close the ongoing requests
                if ("close" === packet.type) {
                    this.onClose({ description: "transport closed by the server" });
                    return false;
                }
                // otherwise bypass onData and handle the message
                this.onPacket(packet);
            };
            // decode payload
            decodePayload(data, this.socket.binaryType).forEach(callback);
            // if an event did not trigger closing
            if ("closed" !== this.readyState) {
                // if we got data we're not polling
                this.polling = false;
                this.emitReserved("pollComplete");
                if ("open" === this.readyState) {
                    this.poll();
                }
            }
        }
        /**
         * For polling, send a close packet.
         *
         * @protected
         */
        doClose() {
            const close = () => {
                this.write([{ type: "close" }]);
            };
            if ("open" === this.readyState) {
                close();
            }
            else {
                // in case we're trying to close while
                // handshaking is in progress (GH-164)
                this.once("open", close);
            }
        }
        /**
         * Writes a packets payload.
         *
         * @param {Array} packets - data packets
         * @protected
         */
        write(packets) {
            this.writable = false;
            encodePayload(packets, (data) => {
                this.doWrite(data, () => {
                    this.writable = true;
                    this.emitReserved("drain");
                });
            });
        }
        /**
         * Generates uri for connection.
         *
         * @private
         */
        uri() {
            let query = this.query || {};
            const schema = this.opts.secure ? "https" : "http";
            let port = "";
            // cache busting is forced
            if (false !== this.opts.timestampRequests) {
                query[this.opts.timestampParam] = yeast();
            }
            if (!this.supportsBinary && !query.sid) {
                query.b64 = 1;
            }
            // avoid port if default for schema
            if (this.opts.port &&
                (("https" === schema && Number(this.opts.port) !== 443) ||
                    ("http" === schema && Number(this.opts.port) !== 80))) {
                port = ":" + this.opts.port;
            }
            const encodedQuery = encode$2(query);
            const ipv6 = this.opts.hostname.indexOf(":") !== -1;
            return (schema +
                "://" +
                (ipv6 ? "[" + this.opts.hostname + "]" : this.opts.hostname) +
                port +
                this.opts.path +
                (encodedQuery.length ? "?" + encodedQuery : ""));
        }
        /**
         * Creates a request.
         *
         * @param {String} method
         * @private
         */
        request(opts = {}) {
            Object.assign(opts, { xd: this.xd, xs: this.xs }, this.opts);
            return new Request(this.uri(), opts);
        }
        /**
         * Sends data.
         *
         * @param {String} data to send.
         * @param {Function} called upon flush.
         * @private
         */
        doWrite(data, fn) {
            const req = this.request({
                method: "POST",
                data: data,
            });
            req.on("success", fn);
            req.on("error", (xhrStatus, context) => {
                this.onError("xhr post error", xhrStatus, context);
            });
        }
        /**
         * Starts a poll cycle.
         *
         * @private
         */
        doPoll() {
            const req = this.request();
            req.on("data", this.onData.bind(this));
            req.on("error", (xhrStatus, context) => {
                this.onError("xhr poll error", xhrStatus, context);
            });
            this.pollXhr = req;
        }
    }
    class Request extends Emitter {
        /**
         * Request constructor
         *
         * @param {Object} options
         * @package
         */
        constructor(uri, opts) {
            super();
            installTimerFunctions(this, opts);
            this.opts = opts;
            this.method = opts.method || "GET";
            this.uri = uri;
            this.async = false !== opts.async;
            this.data = undefined !== opts.data ? opts.data : null;
            this.create();
        }
        /**
         * Creates the XHR object and sends the request.
         *
         * @private
         */
        create() {
            const opts = pick(this.opts, "agent", "pfx", "key", "passphrase", "cert", "ca", "ciphers", "rejectUnauthorized", "autoUnref");
            opts.xdomain = !!this.opts.xd;
            opts.xscheme = !!this.opts.xs;
            const xhr = (this.xhr = new XHR(opts));
            try {
                xhr.open(this.method, this.uri, this.async);
                try {
                    if (this.opts.extraHeaders) {
                        xhr.setDisableHeaderCheck && xhr.setDisableHeaderCheck(true);
                        for (let i in this.opts.extraHeaders) {
                            if (this.opts.extraHeaders.hasOwnProperty(i)) {
                                xhr.setRequestHeader(i, this.opts.extraHeaders[i]);
                            }
                        }
                    }
                }
                catch (e) { }
                if ("POST" === this.method) {
                    try {
                        xhr.setRequestHeader("Content-type", "text/plain;charset=UTF-8");
                    }
                    catch (e) { }
                }
                try {
                    xhr.setRequestHeader("Accept", "*/*");
                }
                catch (e) { }
                // ie6 check
                if ("withCredentials" in xhr) {
                    xhr.withCredentials = this.opts.withCredentials;
                }
                if (this.opts.requestTimeout) {
                    xhr.timeout = this.opts.requestTimeout;
                }
                xhr.onreadystatechange = () => {
                    if (4 !== xhr.readyState)
                        return;
                    if (200 === xhr.status || 1223 === xhr.status) {
                        this.onLoad();
                    }
                    else {
                        // make sure the `error` event handler that's user-set
                        // does not throw in the same tick and gets caught here
                        this.setTimeoutFn(() => {
                            this.onError(typeof xhr.status === "number" ? xhr.status : 0);
                        }, 0);
                    }
                };
                xhr.send(this.data);
            }
            catch (e) {
                // Need to defer since .create() is called directly from the constructor
                // and thus the 'error' event can only be only bound *after* this exception
                // occurs.  Therefore, also, we cannot throw here at all.
                this.setTimeoutFn(() => {
                    this.onError(e);
                }, 0);
                return;
            }
            if (typeof document !== "undefined") {
                this.index = Request.requestsCount++;
                Request.requests[this.index] = this;
            }
        }
        /**
         * Called upon error.
         *
         * @private
         */
        onError(err) {
            this.emitReserved("error", err, this.xhr);
            this.cleanup(true);
        }
        /**
         * Cleans up house.
         *
         * @private
         */
        cleanup(fromError) {
            if ("undefined" === typeof this.xhr || null === this.xhr) {
                return;
            }
            this.xhr.onreadystatechange = empty;
            if (fromError) {
                try {
                    this.xhr.abort();
                }
                catch (e) { }
            }
            if (typeof document !== "undefined") {
                delete Request.requests[this.index];
            }
            this.xhr = null;
        }
        /**
         * Called upon load.
         *
         * @private
         */
        onLoad() {
            const data = this.xhr.responseText;
            if (data !== null) {
                this.emitReserved("data", data);
                this.emitReserved("success");
                this.cleanup();
            }
        }
        /**
         * Aborts the request.
         *
         * @package
         */
        abort() {
            this.cleanup();
        }
    }
    Request.requestsCount = 0;
    Request.requests = {};
    /**
     * Aborts pending requests when unloading the window. This is needed to prevent
     * memory leaks (e.g. when using IE) and to ensure that no spurious error is
     * emitted.
     */
    if (typeof document !== "undefined") {
        // @ts-ignore
        if (typeof attachEvent === "function") {
            // @ts-ignore
            attachEvent("onunload", unloadHandler);
        }
        else if (typeof addEventListener === "function") {
            const terminationEvent = "onpagehide" in globalThisShim ? "pagehide" : "unload";
            addEventListener(terminationEvent, unloadHandler, false);
        }
    }
    function unloadHandler() {
        for (let i in Request.requests) {
            if (Request.requests.hasOwnProperty(i)) {
                Request.requests[i].abort();
            }
        }
    }

    const nextTick = (() => {
        const isPromiseAvailable = typeof Promise === "function" && typeof Promise.resolve === "function";
        if (isPromiseAvailable) {
            return (cb) => Promise.resolve().then(cb);
        }
        else {
            return (cb, setTimeoutFn) => setTimeoutFn(cb, 0);
        }
    })();
    const WebSocket = globalThisShim.WebSocket || globalThisShim.MozWebSocket;
    const usingBrowserWebSocket = true;
    const defaultBinaryType = "arraybuffer";

    // detect ReactNative environment
    const isReactNative = typeof navigator !== "undefined" &&
        typeof navigator.product === "string" &&
        navigator.product.toLowerCase() === "reactnative";
    class WS extends Transport {
        /**
         * WebSocket transport constructor.
         *
         * @param {Object} opts - connection options
         * @protected
         */
        constructor(opts) {
            super(opts);
            this.supportsBinary = !opts.forceBase64;
        }
        get name() {
            return "websocket";
        }
        doOpen() {
            if (!this.check()) {
                // let probe timeout
                return;
            }
            const uri = this.uri();
            const protocols = this.opts.protocols;
            // React Native only supports the 'headers' option, and will print a warning if anything else is passed
            const opts = isReactNative
                ? {}
                : pick(this.opts, "agent", "perMessageDeflate", "pfx", "key", "passphrase", "cert", "ca", "ciphers", "rejectUnauthorized", "localAddress", "protocolVersion", "origin", "maxPayload", "family", "checkServerIdentity");
            if (this.opts.extraHeaders) {
                opts.headers = this.opts.extraHeaders;
            }
            try {
                this.ws =
                    usingBrowserWebSocket && !isReactNative
                        ? protocols
                            ? new WebSocket(uri, protocols)
                            : new WebSocket(uri)
                        : new WebSocket(uri, protocols, opts);
            }
            catch (err) {
                return this.emitReserved("error", err);
            }
            this.ws.binaryType = this.socket.binaryType || defaultBinaryType;
            this.addEventListeners();
        }
        /**
         * Adds event listeners to the socket
         *
         * @private
         */
        addEventListeners() {
            this.ws.onopen = () => {
                if (this.opts.autoUnref) {
                    this.ws._socket.unref();
                }
                this.onOpen();
            };
            this.ws.onclose = (closeEvent) => this.onClose({
                description: "websocket connection closed",
                context: closeEvent,
            });
            this.ws.onmessage = (ev) => this.onData(ev.data);
            this.ws.onerror = (e) => this.onError("websocket error", e);
        }
        write(packets) {
            this.writable = false;
            // encodePacket efficient as it uses WS framing
            // no need for encodePayload
            for (let i = 0; i < packets.length; i++) {
                const packet = packets[i];
                const lastPacket = i === packets.length - 1;
                encodePacket(packet, this.supportsBinary, (data) => {
                    // always create a new object (GH-437)
                    const opts = {};
                    // Sometimes the websocket has already been closed but the browser didn't
                    // have a chance of informing us about it yet, in that case send will
                    // throw an error
                    try {
                        if (usingBrowserWebSocket) {
                            // TypeError is thrown when passing the second argument on Safari
                            this.ws.send(data);
                        }
                    }
                    catch (e) {
                    }
                    if (lastPacket) {
                        // fake drain
                        // defer to next tick to allow Socket to clear writeBuffer
                        nextTick(() => {
                            this.writable = true;
                            this.emitReserved("drain");
                        }, this.setTimeoutFn);
                    }
                });
            }
        }
        doClose() {
            if (typeof this.ws !== "undefined") {
                this.ws.close();
                this.ws = null;
            }
        }
        /**
         * Generates uri for connection.
         *
         * @private
         */
        uri() {
            let query = this.query || {};
            const schema = this.opts.secure ? "wss" : "ws";
            let port = "";
            // avoid port if default for schema
            if (this.opts.port &&
                (("wss" === schema && Number(this.opts.port) !== 443) ||
                    ("ws" === schema && Number(this.opts.port) !== 80))) {
                port = ":" + this.opts.port;
            }
            // append timestamp to URI
            if (this.opts.timestampRequests) {
                query[this.opts.timestampParam] = yeast();
            }
            // communicate binary support capabilities
            if (!this.supportsBinary) {
                query.b64 = 1;
            }
            const encodedQuery = encode$2(query);
            const ipv6 = this.opts.hostname.indexOf(":") !== -1;
            return (schema +
                "://" +
                (ipv6 ? "[" + this.opts.hostname + "]" : this.opts.hostname) +
                port +
                this.opts.path +
                (encodedQuery.length ? "?" + encodedQuery : ""));
        }
        /**
         * Feature detection for WebSocket.
         *
         * @return {Boolean} whether this transport is available.
         * @private
         */
        check() {
            return !!WebSocket;
        }
    }

    const transports = {
        websocket: WS,
        polling: Polling,
    };

    // imported from https://github.com/galkn/parseuri
    /**
     * Parses a URI
     *
     * Note: we could also have used the built-in URL object, but it isn't supported on all platforms.
     *
     * See:
     * - https://developer.mozilla.org/en-US/docs/Web/API/URL
     * - https://caniuse.com/url
     * - https://www.rfc-editor.org/rfc/rfc3986#appendix-B
     *
     * History of the parse() method:
     * - first commit: https://github.com/socketio/socket.io-client/commit/4ee1d5d94b3906a9c052b459f1a818b15f38f91c
     * - export into its own module: https://github.com/socketio/engine.io-client/commit/de2c561e4564efeb78f1bdb1ba39ef81b2822cb3
     * - reimport: https://github.com/socketio/engine.io-client/commit/df32277c3f6d622eec5ed09f493cae3f3391d242
     *
     * @author Steven Levithan <stevenlevithan.com> (MIT license)
     * @api private
     */
    const re = /^(?:(?![^:@\/?#]+:[^:@\/]*@)(http|https|ws|wss):\/\/)?((?:(([^:@\/?#]*)(?::([^:@\/?#]*))?)?@)?((?:[a-f0-9]{0,4}:){2,7}[a-f0-9]{0,4}|[^:\/?#]*)(?::(\d*))?)(((\/(?:[^?#](?![^?#\/]*\.[^?#\/.]+(?:[?#]|$)))*\/?)?([^?#\/]*))(?:\?([^#]*))?(?:#(.*))?)/;
    const parts = [
        'source', 'protocol', 'authority', 'userInfo', 'user', 'password', 'host', 'port', 'relative', 'path', 'directory', 'file', 'query', 'anchor'
    ];
    function parse(str) {
        const src = str, b = str.indexOf('['), e = str.indexOf(']');
        if (b != -1 && e != -1) {
            str = str.substring(0, b) + str.substring(b, e).replace(/:/g, ';') + str.substring(e, str.length);
        }
        let m = re.exec(str || ''), uri = {}, i = 14;
        while (i--) {
            uri[parts[i]] = m[i] || '';
        }
        if (b != -1 && e != -1) {
            uri.source = src;
            uri.host = uri.host.substring(1, uri.host.length - 1).replace(/;/g, ':');
            uri.authority = uri.authority.replace('[', '').replace(']', '').replace(/;/g, ':');
            uri.ipv6uri = true;
        }
        uri.pathNames = pathNames(uri, uri['path']);
        uri.queryKey = queryKey(uri, uri['query']);
        return uri;
    }
    function pathNames(obj, path) {
        const regx = /\/{2,9}/g, names = path.replace(regx, "/").split("/");
        if (path.slice(0, 1) == '/' || path.length === 0) {
            names.splice(0, 1);
        }
        if (path.slice(-1) == '/') {
            names.splice(names.length - 1, 1);
        }
        return names;
    }
    function queryKey(uri, query) {
        const data = {};
        query.replace(/(?:^|&)([^&=]*)=?([^&]*)/g, function ($0, $1, $2) {
            if ($1) {
                data[$1] = $2;
            }
        });
        return data;
    }

    let Socket$1 = class Socket extends Emitter {
        /**
         * Socket constructor.
         *
         * @param {String|Object} uri - uri or options
         * @param {Object} opts - options
         */
        constructor(uri, opts = {}) {
            super();
            this.writeBuffer = [];
            if (uri && "object" === typeof uri) {
                opts = uri;
                uri = null;
            }
            if (uri) {
                uri = parse(uri);
                opts.hostname = uri.host;
                opts.secure = uri.protocol === "https" || uri.protocol === "wss";
                opts.port = uri.port;
                if (uri.query)
                    opts.query = uri.query;
            }
            else if (opts.host) {
                opts.hostname = parse(opts.host).host;
            }
            installTimerFunctions(this, opts);
            this.secure =
                null != opts.secure
                    ? opts.secure
                    : typeof location !== "undefined" && "https:" === location.protocol;
            if (opts.hostname && !opts.port) {
                // if no port is specified manually, use the protocol default
                opts.port = this.secure ? "443" : "80";
            }
            this.hostname =
                opts.hostname ||
                    (typeof location !== "undefined" ? location.hostname : "localhost");
            this.port =
                opts.port ||
                    (typeof location !== "undefined" && location.port
                        ? location.port
                        : this.secure
                            ? "443"
                            : "80");
            this.transports = opts.transports || ["polling", "websocket"];
            this.writeBuffer = [];
            this.prevBufferLen = 0;
            this.opts = Object.assign({
                path: "/engine.io",
                agent: false,
                withCredentials: false,
                upgrade: true,
                timestampParam: "t",
                rememberUpgrade: false,
                addTrailingSlash: true,
                rejectUnauthorized: true,
                perMessageDeflate: {
                    threshold: 1024,
                },
                transportOptions: {},
                closeOnBeforeunload: true,
            }, opts);
            this.opts.path =
                this.opts.path.replace(/\/$/, "") +
                    (this.opts.addTrailingSlash ? "/" : "");
            if (typeof this.opts.query === "string") {
                this.opts.query = decode(this.opts.query);
            }
            // set on handshake
            this.id = null;
            this.upgrades = null;
            this.pingInterval = null;
            this.pingTimeout = null;
            // set on heartbeat
            this.pingTimeoutTimer = null;
            if (typeof addEventListener === "function") {
                if (this.opts.closeOnBeforeunload) {
                    // Firefox closes the connection when the "beforeunload" event is emitted but not Chrome. This event listener
                    // ensures every browser behaves the same (no "disconnect" event at the Socket.IO level when the page is
                    // closed/reloaded)
                    this.beforeunloadEventListener = () => {
                        if (this.transport) {
                            // silently close the transport
                            this.transport.removeAllListeners();
                            this.transport.close();
                        }
                    };
                    addEventListener("beforeunload", this.beforeunloadEventListener, false);
                }
                if (this.hostname !== "localhost") {
                    this.offlineEventListener = () => {
                        this.onClose("transport close", {
                            description: "network connection lost",
                        });
                    };
                    addEventListener("offline", this.offlineEventListener, false);
                }
            }
            this.open();
        }
        /**
         * Creates transport of the given type.
         *
         * @param {String} name - transport name
         * @return {Transport}
         * @private
         */
        createTransport(name) {
            const query = Object.assign({}, this.opts.query);
            // append engine.io protocol identifier
            query.EIO = protocol$1;
            // transport name
            query.transport = name;
            // session id if we already have one
            if (this.id)
                query.sid = this.id;
            const opts = Object.assign({}, this.opts.transportOptions[name], this.opts, {
                query,
                socket: this,
                hostname: this.hostname,
                secure: this.secure,
                port: this.port,
            });
            return new transports[name](opts);
        }
        /**
         * Initializes transport to use and starts probe.
         *
         * @private
         */
        open() {
            let transport;
            if (this.opts.rememberUpgrade &&
                Socket.priorWebsocketSuccess &&
                this.transports.indexOf("websocket") !== -1) {
                transport = "websocket";
            }
            else if (0 === this.transports.length) {
                // Emit error on next tick so it can be listened to
                this.setTimeoutFn(() => {
                    this.emitReserved("error", "No transports available");
                }, 0);
                return;
            }
            else {
                transport = this.transports[0];
            }
            this.readyState = "opening";
            // Retry with the next transport if the transport is disabled (jsonp: false)
            try {
                transport = this.createTransport(transport);
            }
            catch (e) {
                this.transports.shift();
                this.open();
                return;
            }
            transport.open();
            this.setTransport(transport);
        }
        /**
         * Sets the current transport. Disables the existing one (if any).
         *
         * @private
         */
        setTransport(transport) {
            if (this.transport) {
                this.transport.removeAllListeners();
            }
            // set up transport
            this.transport = transport;
            // set up transport listeners
            transport
                .on("drain", this.onDrain.bind(this))
                .on("packet", this.onPacket.bind(this))
                .on("error", this.onError.bind(this))
                .on("close", (reason) => this.onClose("transport close", reason));
        }
        /**
         * Probes a transport.
         *
         * @param {String} name - transport name
         * @private
         */
        probe(name) {
            let transport = this.createTransport(name);
            let failed = false;
            Socket.priorWebsocketSuccess = false;
            const onTransportOpen = () => {
                if (failed)
                    return;
                transport.send([{ type: "ping", data: "probe" }]);
                transport.once("packet", (msg) => {
                    if (failed)
                        return;
                    if ("pong" === msg.type && "probe" === msg.data) {
                        this.upgrading = true;
                        this.emitReserved("upgrading", transport);
                        if (!transport)
                            return;
                        Socket.priorWebsocketSuccess = "websocket" === transport.name;
                        this.transport.pause(() => {
                            if (failed)
                                return;
                            if ("closed" === this.readyState)
                                return;
                            cleanup();
                            this.setTransport(transport);
                            transport.send([{ type: "upgrade" }]);
                            this.emitReserved("upgrade", transport);
                            transport = null;
                            this.upgrading = false;
                            this.flush();
                        });
                    }
                    else {
                        const err = new Error("probe error");
                        // @ts-ignore
                        err.transport = transport.name;
                        this.emitReserved("upgradeError", err);
                    }
                });
            };
            function freezeTransport() {
                if (failed)
                    return;
                // Any callback called by transport should be ignored since now
                failed = true;
                cleanup();
                transport.close();
                transport = null;
            }
            // Handle any error that happens while probing
            const onerror = (err) => {
                const error = new Error("probe error: " + err);
                // @ts-ignore
                error.transport = transport.name;
                freezeTransport();
                this.emitReserved("upgradeError", error);
            };
            function onTransportClose() {
                onerror("transport closed");
            }
            // When the socket is closed while we're probing
            function onclose() {
                onerror("socket closed");
            }
            // When the socket is upgraded while we're probing
            function onupgrade(to) {
                if (transport && to.name !== transport.name) {
                    freezeTransport();
                }
            }
            // Remove all listeners on the transport and on self
            const cleanup = () => {
                transport.removeListener("open", onTransportOpen);
                transport.removeListener("error", onerror);
                transport.removeListener("close", onTransportClose);
                this.off("close", onclose);
                this.off("upgrading", onupgrade);
            };
            transport.once("open", onTransportOpen);
            transport.once("error", onerror);
            transport.once("close", onTransportClose);
            this.once("close", onclose);
            this.once("upgrading", onupgrade);
            transport.open();
        }
        /**
         * Called when connection is deemed open.
         *
         * @private
         */
        onOpen() {
            this.readyState = "open";
            Socket.priorWebsocketSuccess = "websocket" === this.transport.name;
            this.emitReserved("open");
            this.flush();
            // we check for `readyState` in case an `open`
            // listener already closed the socket
            if ("open" === this.readyState && this.opts.upgrade) {
                let i = 0;
                const l = this.upgrades.length;
                for (; i < l; i++) {
                    this.probe(this.upgrades[i]);
                }
            }
        }
        /**
         * Handles a packet.
         *
         * @private
         */
        onPacket(packet) {
            if ("opening" === this.readyState ||
                "open" === this.readyState ||
                "closing" === this.readyState) {
                this.emitReserved("packet", packet);
                // Socket is live - any packet counts
                this.emitReserved("heartbeat");
                switch (packet.type) {
                    case "open":
                        this.onHandshake(JSON.parse(packet.data));
                        break;
                    case "ping":
                        this.resetPingTimeout();
                        this.sendPacket("pong");
                        this.emitReserved("ping");
                        this.emitReserved("pong");
                        break;
                    case "error":
                        const err = new Error("server error");
                        // @ts-ignore
                        err.code = packet.data;
                        this.onError(err);
                        break;
                    case "message":
                        this.emitReserved("data", packet.data);
                        this.emitReserved("message", packet.data);
                        break;
                }
            }
        }
        /**
         * Called upon handshake completion.
         *
         * @param {Object} data - handshake obj
         * @private
         */
        onHandshake(data) {
            this.emitReserved("handshake", data);
            this.id = data.sid;
            this.transport.query.sid = data.sid;
            this.upgrades = this.filterUpgrades(data.upgrades);
            this.pingInterval = data.pingInterval;
            this.pingTimeout = data.pingTimeout;
            this.maxPayload = data.maxPayload;
            this.onOpen();
            // In case open handler closes socket
            if ("closed" === this.readyState)
                return;
            this.resetPingTimeout();
        }
        /**
         * Sets and resets ping timeout timer based on server pings.
         *
         * @private
         */
        resetPingTimeout() {
            this.clearTimeoutFn(this.pingTimeoutTimer);
            this.pingTimeoutTimer = this.setTimeoutFn(() => {
                this.onClose("ping timeout");
            }, this.pingInterval + this.pingTimeout);
            if (this.opts.autoUnref) {
                this.pingTimeoutTimer.unref();
            }
        }
        /**
         * Called on `drain` event
         *
         * @private
         */
        onDrain() {
            this.writeBuffer.splice(0, this.prevBufferLen);
            // setting prevBufferLen = 0 is very important
            // for example, when upgrading, upgrade packet is sent over,
            // and a nonzero prevBufferLen could cause problems on `drain`
            this.prevBufferLen = 0;
            if (0 === this.writeBuffer.length) {
                this.emitReserved("drain");
            }
            else {
                this.flush();
            }
        }
        /**
         * Flush write buffers.
         *
         * @private
         */
        flush() {
            if ("closed" !== this.readyState &&
                this.transport.writable &&
                !this.upgrading &&
                this.writeBuffer.length) {
                const packets = this.getWritablePackets();
                this.transport.send(packets);
                // keep track of current length of writeBuffer
                // splice writeBuffer and callbackBuffer on `drain`
                this.prevBufferLen = packets.length;
                this.emitReserved("flush");
            }
        }
        /**
         * Ensure the encoded size of the writeBuffer is below the maxPayload value sent by the server (only for HTTP
         * long-polling)
         *
         * @private
         */
        getWritablePackets() {
            const shouldCheckPayloadSize = this.maxPayload &&
                this.transport.name === "polling" &&
                this.writeBuffer.length > 1;
            if (!shouldCheckPayloadSize) {
                return this.writeBuffer;
            }
            let payloadSize = 1; // first packet type
            for (let i = 0; i < this.writeBuffer.length; i++) {
                const data = this.writeBuffer[i].data;
                if (data) {
                    payloadSize += byteLength(data);
                }
                if (i > 0 && payloadSize > this.maxPayload) {
                    return this.writeBuffer.slice(0, i);
                }
                payloadSize += 2; // separator + packet type
            }
            return this.writeBuffer;
        }
        /**
         * Sends a message.
         *
         * @param {String} msg - message.
         * @param {Object} options.
         * @param {Function} callback function.
         * @return {Socket} for chaining.
         */
        write(msg, options, fn) {
            this.sendPacket("message", msg, options, fn);
            return this;
        }
        send(msg, options, fn) {
            this.sendPacket("message", msg, options, fn);
            return this;
        }
        /**
         * Sends a packet.
         *
         * @param {String} type: packet type.
         * @param {String} data.
         * @param {Object} options.
         * @param {Function} fn - callback function.
         * @private
         */
        sendPacket(type, data, options, fn) {
            if ("function" === typeof data) {
                fn = data;
                data = undefined;
            }
            if ("function" === typeof options) {
                fn = options;
                options = null;
            }
            if ("closing" === this.readyState || "closed" === this.readyState) {
                return;
            }
            options = options || {};
            options.compress = false !== options.compress;
            const packet = {
                type: type,
                data: data,
                options: options,
            };
            this.emitReserved("packetCreate", packet);
            this.writeBuffer.push(packet);
            if (fn)
                this.once("flush", fn);
            this.flush();
        }
        /**
         * Closes the connection.
         */
        close() {
            const close = () => {
                this.onClose("forced close");
                this.transport.close();
            };
            const cleanupAndClose = () => {
                this.off("upgrade", cleanupAndClose);
                this.off("upgradeError", cleanupAndClose);
                close();
            };
            const waitForUpgrade = () => {
                // wait for upgrade to finish since we can't send packets while pausing a transport
                this.once("upgrade", cleanupAndClose);
                this.once("upgradeError", cleanupAndClose);
            };
            if ("opening" === this.readyState || "open" === this.readyState) {
                this.readyState = "closing";
                if (this.writeBuffer.length) {
                    this.once("drain", () => {
                        if (this.upgrading) {
                            waitForUpgrade();
                        }
                        else {
                            close();
                        }
                    });
                }
                else if (this.upgrading) {
                    waitForUpgrade();
                }
                else {
                    close();
                }
            }
            return this;
        }
        /**
         * Called upon transport error
         *
         * @private
         */
        onError(err) {
            Socket.priorWebsocketSuccess = false;
            this.emitReserved("error", err);
            this.onClose("transport error", err);
        }
        /**
         * Called upon transport close.
         *
         * @private
         */
        onClose(reason, description) {
            if ("opening" === this.readyState ||
                "open" === this.readyState ||
                "closing" === this.readyState) {
                // clear timers
                this.clearTimeoutFn(this.pingTimeoutTimer);
                // stop event from firing again for transport
                this.transport.removeAllListeners("close");
                // ensure transport won't stay open
                this.transport.close();
                // ignore further transport communication
                this.transport.removeAllListeners();
                if (typeof removeEventListener === "function") {
                    removeEventListener("beforeunload", this.beforeunloadEventListener, false);
                    removeEventListener("offline", this.offlineEventListener, false);
                }
                // set ready state
                this.readyState = "closed";
                // clear session id
                this.id = null;
                // emit close event
                this.emitReserved("close", reason, description);
                // clean buffers after, so users can still
                // grab the buffers on `close` event
                this.writeBuffer = [];
                this.prevBufferLen = 0;
            }
        }
        /**
         * Filters upgrades, returning only those matching client transports.
         *
         * @param {Array} upgrades - server upgrades
         * @private
         */
        filterUpgrades(upgrades) {
            const filteredUpgrades = [];
            let i = 0;
            const j = upgrades.length;
            for (; i < j; i++) {
                if (~this.transports.indexOf(upgrades[i]))
                    filteredUpgrades.push(upgrades[i]);
            }
            return filteredUpgrades;
        }
    };
    Socket$1.protocol = protocol$1;

    /**
     * URL parser.
     *
     * @param uri - url
     * @param path - the request path of the connection
     * @param loc - An object meant to mimic window.location.
     *        Defaults to window.location.
     * @public
     */
    function url(uri, path = "", loc) {
        let obj = uri;
        // default to window.location
        loc = loc || (typeof location !== "undefined" && location);
        if (null == uri)
            uri = loc.protocol + "//" + loc.host;
        // relative path support
        if (typeof uri === "string") {
            if ("/" === uri.charAt(0)) {
                if ("/" === uri.charAt(1)) {
                    uri = loc.protocol + uri;
                }
                else {
                    uri = loc.host + uri;
                }
            }
            if (!/^(https?|wss?):\/\//.test(uri)) {
                if ("undefined" !== typeof loc) {
                    uri = loc.protocol + "//" + uri;
                }
                else {
                    uri = "https://" + uri;
                }
            }
            // parse
            obj = parse(uri);
        }
        // make sure we treat `localhost:80` and `localhost` equally
        if (!obj.port) {
            if (/^(http|ws)$/.test(obj.protocol)) {
                obj.port = "80";
            }
            else if (/^(http|ws)s$/.test(obj.protocol)) {
                obj.port = "443";
            }
        }
        obj.path = obj.path || "/";
        const ipv6 = obj.host.indexOf(":") !== -1;
        const host = ipv6 ? "[" + obj.host + "]" : obj.host;
        // define unique id
        obj.id = obj.protocol + "://" + host + ":" + obj.port + path;
        // define href
        obj.href =
            obj.protocol +
                "://" +
                host +
                (loc && loc.port === obj.port ? "" : ":" + obj.port);
        return obj;
    }

    const withNativeArrayBuffer = typeof ArrayBuffer === "function";
    const isView = (obj) => {
        return typeof ArrayBuffer.isView === "function"
            ? ArrayBuffer.isView(obj)
            : obj.buffer instanceof ArrayBuffer;
    };
    const toString$1 = Object.prototype.toString;
    const withNativeBlob = typeof Blob === "function" ||
        (typeof Blob !== "undefined" &&
            toString$1.call(Blob) === "[object BlobConstructor]");
    const withNativeFile = typeof File === "function" ||
        (typeof File !== "undefined" &&
            toString$1.call(File) === "[object FileConstructor]");
    /**
     * Returns true if obj is a Buffer, an ArrayBuffer, a Blob or a File.
     *
     * @private
     */
    function isBinary(obj) {
        return ((withNativeArrayBuffer && (obj instanceof ArrayBuffer || isView(obj))) ||
            (withNativeBlob && obj instanceof Blob) ||
            (withNativeFile && obj instanceof File));
    }
    function hasBinary(obj, toJSON) {
        if (!obj || typeof obj !== "object") {
            return false;
        }
        if (Array.isArray(obj)) {
            for (let i = 0, l = obj.length; i < l; i++) {
                if (hasBinary(obj[i])) {
                    return true;
                }
            }
            return false;
        }
        if (isBinary(obj)) {
            return true;
        }
        if (obj.toJSON &&
            typeof obj.toJSON === "function" &&
            arguments.length === 1) {
            return hasBinary(obj.toJSON(), true);
        }
        for (const key in obj) {
            if (Object.prototype.hasOwnProperty.call(obj, key) && hasBinary(obj[key])) {
                return true;
            }
        }
        return false;
    }

    /**
     * Replaces every Buffer | ArrayBuffer | Blob | File in packet with a numbered placeholder.
     *
     * @param {Object} packet - socket.io event packet
     * @return {Object} with deconstructed packet and list of buffers
     * @public
     */
    function deconstructPacket(packet) {
        const buffers = [];
        const packetData = packet.data;
        const pack = packet;
        pack.data = _deconstructPacket(packetData, buffers);
        pack.attachments = buffers.length; // number of binary 'attachments'
        return { packet: pack, buffers: buffers };
    }
    function _deconstructPacket(data, buffers) {
        if (!data)
            return data;
        if (isBinary(data)) {
            const placeholder = { _placeholder: true, num: buffers.length };
            buffers.push(data);
            return placeholder;
        }
        else if (Array.isArray(data)) {
            const newData = new Array(data.length);
            for (let i = 0; i < data.length; i++) {
                newData[i] = _deconstructPacket(data[i], buffers);
            }
            return newData;
        }
        else if (typeof data === "object" && !(data instanceof Date)) {
            const newData = {};
            for (const key in data) {
                if (Object.prototype.hasOwnProperty.call(data, key)) {
                    newData[key] = _deconstructPacket(data[key], buffers);
                }
            }
            return newData;
        }
        return data;
    }
    /**
     * Reconstructs a binary packet from its placeholder packet and buffers
     *
     * @param {Object} packet - event packet with placeholders
     * @param {Array} buffers - binary buffers to put in placeholder positions
     * @return {Object} reconstructed packet
     * @public
     */
    function reconstructPacket(packet, buffers) {
        packet.data = _reconstructPacket(packet.data, buffers);
        delete packet.attachments; // no longer useful
        return packet;
    }
    function _reconstructPacket(data, buffers) {
        if (!data)
            return data;
        if (data && data._placeholder === true) {
            const isIndexValid = typeof data.num === "number" &&
                data.num >= 0 &&
                data.num < buffers.length;
            if (isIndexValid) {
                return buffers[data.num]; // appropriate buffer (should be natural order anyway)
            }
            else {
                throw new Error("illegal attachments");
            }
        }
        else if (Array.isArray(data)) {
            for (let i = 0; i < data.length; i++) {
                data[i] = _reconstructPacket(data[i], buffers);
            }
        }
        else if (typeof data === "object") {
            for (const key in data) {
                if (Object.prototype.hasOwnProperty.call(data, key)) {
                    data[key] = _reconstructPacket(data[key], buffers);
                }
            }
        }
        return data;
    }

    /**
     * These strings must not be used as event names, as they have a special meaning.
     */
    const RESERVED_EVENTS$1 = [
        "connect",
        "connect_error",
        "disconnect",
        "disconnecting",
        "newListener",
        "removeListener", // used by the Node.js EventEmitter
    ];
    /**
     * Protocol version.
     *
     * @public
     */
    const protocol = 5;
    var PacketType;
    (function (PacketType) {
        PacketType[PacketType["CONNECT"] = 0] = "CONNECT";
        PacketType[PacketType["DISCONNECT"] = 1] = "DISCONNECT";
        PacketType[PacketType["EVENT"] = 2] = "EVENT";
        PacketType[PacketType["ACK"] = 3] = "ACK";
        PacketType[PacketType["CONNECT_ERROR"] = 4] = "CONNECT_ERROR";
        PacketType[PacketType["BINARY_EVENT"] = 5] = "BINARY_EVENT";
        PacketType[PacketType["BINARY_ACK"] = 6] = "BINARY_ACK";
    })(PacketType || (PacketType = {}));
    /**
     * A socket.io Encoder instance
     */
    class Encoder {
        /**
         * Encoder constructor
         *
         * @param {function} replacer - custom replacer to pass down to JSON.parse
         */
        constructor(replacer) {
            this.replacer = replacer;
        }
        /**
         * Encode a packet as a single string if non-binary, or as a
         * buffer sequence, depending on packet type.
         *
         * @param {Object} obj - packet object
         */
        encode(obj) {
            if (obj.type === PacketType.EVENT || obj.type === PacketType.ACK) {
                if (hasBinary(obj)) {
                    return this.encodeAsBinary({
                        type: obj.type === PacketType.EVENT
                            ? PacketType.BINARY_EVENT
                            : PacketType.BINARY_ACK,
                        nsp: obj.nsp,
                        data: obj.data,
                        id: obj.id,
                    });
                }
            }
            return [this.encodeAsString(obj)];
        }
        /**
         * Encode packet as string.
         */
        encodeAsString(obj) {
            // first is type
            let str = "" + obj.type;
            // attachments if we have them
            if (obj.type === PacketType.BINARY_EVENT ||
                obj.type === PacketType.BINARY_ACK) {
                str += obj.attachments + "-";
            }
            // if we have a namespace other than `/`
            // we append it followed by a comma `,`
            if (obj.nsp && "/" !== obj.nsp) {
                str += obj.nsp + ",";
            }
            // immediately followed by the id
            if (null != obj.id) {
                str += obj.id;
            }
            // json data
            if (null != obj.data) {
                str += JSON.stringify(obj.data, this.replacer);
            }
            return str;
        }
        /**
         * Encode packet as 'buffer sequence' by removing blobs, and
         * deconstructing packet into object with placeholders and
         * a list of buffers.
         */
        encodeAsBinary(obj) {
            const deconstruction = deconstructPacket(obj);
            const pack = this.encodeAsString(deconstruction.packet);
            const buffers = deconstruction.buffers;
            buffers.unshift(pack); // add packet info to beginning of data list
            return buffers; // write all the buffers
        }
    }
    // see https://stackoverflow.com/questions/8511281/check-if-a-value-is-an-object-in-javascript
    function isObject$1(value) {
        return Object.prototype.toString.call(value) === "[object Object]";
    }
    /**
     * A socket.io Decoder instance
     *
     * @return {Object} decoder
     */
    class Decoder extends Emitter {
        /**
         * Decoder constructor
         *
         * @param {function} reviver - custom reviver to pass down to JSON.stringify
         */
        constructor(reviver) {
            super();
            this.reviver = reviver;
        }
        /**
         * Decodes an encoded packet string into packet JSON.
         *
         * @param {String} obj - encoded packet
         */
        add(obj) {
            let packet;
            if (typeof obj === "string") {
                if (this.reconstructor) {
                    throw new Error("got plaintext data when reconstructing a packet");
                }
                packet = this.decodeString(obj);
                const isBinaryEvent = packet.type === PacketType.BINARY_EVENT;
                if (isBinaryEvent || packet.type === PacketType.BINARY_ACK) {
                    packet.type = isBinaryEvent ? PacketType.EVENT : PacketType.ACK;
                    // binary packet's json
                    this.reconstructor = new BinaryReconstructor(packet);
                    // no attachments, labeled binary but no binary data to follow
                    if (packet.attachments === 0) {
                        super.emitReserved("decoded", packet);
                    }
                }
                else {
                    // non-binary full packet
                    super.emitReserved("decoded", packet);
                }
            }
            else if (isBinary(obj) || obj.base64) {
                // raw binary data
                if (!this.reconstructor) {
                    throw new Error("got binary data when not reconstructing a packet");
                }
                else {
                    packet = this.reconstructor.takeBinaryData(obj);
                    if (packet) {
                        // received final buffer
                        this.reconstructor = null;
                        super.emitReserved("decoded", packet);
                    }
                }
            }
            else {
                throw new Error("Unknown type: " + obj);
            }
        }
        /**
         * Decode a packet String (JSON data)
         *
         * @param {String} str
         * @return {Object} packet
         */
        decodeString(str) {
            let i = 0;
            // look up type
            const p = {
                type: Number(str.charAt(0)),
            };
            if (PacketType[p.type] === undefined) {
                throw new Error("unknown packet type " + p.type);
            }
            // look up attachments if type binary
            if (p.type === PacketType.BINARY_EVENT ||
                p.type === PacketType.BINARY_ACK) {
                const start = i + 1;
                while (str.charAt(++i) !== "-" && i != str.length) { }
                const buf = str.substring(start, i);
                if (buf != Number(buf) || str.charAt(i) !== "-") {
                    throw new Error("Illegal attachments");
                }
                p.attachments = Number(buf);
            }
            // look up namespace (if any)
            if ("/" === str.charAt(i + 1)) {
                const start = i + 1;
                while (++i) {
                    const c = str.charAt(i);
                    if ("," === c)
                        break;
                    if (i === str.length)
                        break;
                }
                p.nsp = str.substring(start, i);
            }
            else {
                p.nsp = "/";
            }
            // look up id
            const next = str.charAt(i + 1);
            if ("" !== next && Number(next) == next) {
                const start = i + 1;
                while (++i) {
                    const c = str.charAt(i);
                    if (null == c || Number(c) != c) {
                        --i;
                        break;
                    }
                    if (i === str.length)
                        break;
                }
                p.id = Number(str.substring(start, i + 1));
            }
            // look up json data
            if (str.charAt(++i)) {
                const payload = this.tryParse(str.substr(i));
                if (Decoder.isPayloadValid(p.type, payload)) {
                    p.data = payload;
                }
                else {
                    throw new Error("invalid payload");
                }
            }
            return p;
        }
        tryParse(str) {
            try {
                return JSON.parse(str, this.reviver);
            }
            catch (e) {
                return false;
            }
        }
        static isPayloadValid(type, payload) {
            switch (type) {
                case PacketType.CONNECT:
                    return isObject$1(payload);
                case PacketType.DISCONNECT:
                    return payload === undefined;
                case PacketType.CONNECT_ERROR:
                    return typeof payload === "string" || isObject$1(payload);
                case PacketType.EVENT:
                case PacketType.BINARY_EVENT:
                    return (Array.isArray(payload) &&
                        (typeof payload[0] === "number" ||
                            (typeof payload[0] === "string" &&
                                RESERVED_EVENTS$1.indexOf(payload[0]) === -1)));
                case PacketType.ACK:
                case PacketType.BINARY_ACK:
                    return Array.isArray(payload);
            }
        }
        /**
         * Deallocates a parser's resources
         */
        destroy() {
            if (this.reconstructor) {
                this.reconstructor.finishedReconstruction();
                this.reconstructor = null;
            }
        }
    }
    /**
     * A manager of a binary event's 'buffer sequence'. Should
     * be constructed whenever a packet of type BINARY_EVENT is
     * decoded.
     *
     * @param {Object} packet
     * @return {BinaryReconstructor} initialized reconstructor
     */
    class BinaryReconstructor {
        constructor(packet) {
            this.packet = packet;
            this.buffers = [];
            this.reconPack = packet;
        }
        /**
         * Method to be called when binary data received from connection
         * after a BINARY_EVENT packet.
         *
         * @param {Buffer | ArrayBuffer} binData - the raw binary data received
         * @return {null | Object} returns null if more binary data is expected or
         *   a reconstructed packet object if all buffers have been received.
         */
        takeBinaryData(binData) {
            this.buffers.push(binData);
            if (this.buffers.length === this.reconPack.attachments) {
                // done with buffer list
                const packet = reconstructPacket(this.reconPack, this.buffers);
                this.finishedReconstruction();
                return packet;
            }
            return null;
        }
        /**
         * Cleans up binary packet reconstruction variables.
         */
        finishedReconstruction() {
            this.reconPack = null;
            this.buffers = [];
        }
    }

    var parser = /*#__PURE__*/Object.freeze({
        __proto__: null,
        Decoder: Decoder,
        Encoder: Encoder,
        get PacketType () { return PacketType; },
        protocol: protocol
    });

    function on(obj, ev, fn) {
        obj.on(ev, fn);
        return function subDestroy() {
            obj.off(ev, fn);
        };
    }

    /**
     * Internal events.
     * These events can't be emitted by the user.
     */
    const RESERVED_EVENTS = Object.freeze({
        connect: 1,
        connect_error: 1,
        disconnect: 1,
        disconnecting: 1,
        // EventEmitter reserved events: https://nodejs.org/api/events.html#events_event_newlistener
        newListener: 1,
        removeListener: 1,
    });
    /**
     * A Socket is the fundamental class for interacting with the server.
     *
     * A Socket belongs to a certain Namespace (by default /) and uses an underlying {@link Manager} to communicate.
     *
     * @example
     * const socket = io();
     *
     * socket.on("connect", () => {
     *   console.log("connected");
     * });
     *
     * // send an event to the server
     * socket.emit("foo", "bar");
     *
     * socket.on("foobar", () => {
     *   // an event was received from the server
     * });
     *
     * // upon disconnection
     * socket.on("disconnect", (reason) => {
     *   console.log(`disconnected due to ${reason}`);
     * });
     */
    class Socket extends Emitter {
        /**
         * `Socket` constructor.
         */
        constructor(io, nsp, opts) {
            super();
            /**
             * Whether the socket is currently connected to the server.
             *
             * @example
             * const socket = io();
             *
             * socket.on("connect", () => {
             *   console.log(socket.connected); // true
             * });
             *
             * socket.on("disconnect", () => {
             *   console.log(socket.connected); // false
             * });
             */
            this.connected = false;
            /**
             * Whether the connection state was recovered after a temporary disconnection. In that case, any missed packets will
             * be transmitted by the server.
             */
            this.recovered = false;
            /**
             * Buffer for packets received before the CONNECT packet
             */
            this.receiveBuffer = [];
            /**
             * Buffer for packets that will be sent once the socket is connected
             */
            this.sendBuffer = [];
            /**
             * The queue of packets to be sent with retry in case of failure.
             *
             * Packets are sent one by one, each waiting for the server acknowledgement, in order to guarantee the delivery order.
             * @private
             */
            this._queue = [];
            /**
             * A sequence to generate the ID of the {@link QueuedPacket}.
             * @private
             */
            this._queueSeq = 0;
            this.ids = 0;
            this.acks = {};
            this.flags = {};
            this.io = io;
            this.nsp = nsp;
            if (opts && opts.auth) {
                this.auth = opts.auth;
            }
            this._opts = Object.assign({}, opts);
            if (this.io._autoConnect)
                this.open();
        }
        /**
         * Whether the socket is currently disconnected
         *
         * @example
         * const socket = io();
         *
         * socket.on("connect", () => {
         *   console.log(socket.disconnected); // false
         * });
         *
         * socket.on("disconnect", () => {
         *   console.log(socket.disconnected); // true
         * });
         */
        get disconnected() {
            return !this.connected;
        }
        /**
         * Subscribe to open, close and packet events
         *
         * @private
         */
        subEvents() {
            if (this.subs)
                return;
            const io = this.io;
            this.subs = [
                on(io, "open", this.onopen.bind(this)),
                on(io, "packet", this.onpacket.bind(this)),
                on(io, "error", this.onerror.bind(this)),
                on(io, "close", this.onclose.bind(this)),
            ];
        }
        /**
         * Whether the Socket will try to reconnect when its Manager connects or reconnects.
         *
         * @example
         * const socket = io();
         *
         * console.log(socket.active); // true
         *
         * socket.on("disconnect", (reason) => {
         *   if (reason === "io server disconnect") {
         *     // the disconnection was initiated by the server, you need to manually reconnect
         *     console.log(socket.active); // false
         *   }
         *   // else the socket will automatically try to reconnect
         *   console.log(socket.active); // true
         * });
         */
        get active() {
            return !!this.subs;
        }
        /**
         * "Opens" the socket.
         *
         * @example
         * const socket = io({
         *   autoConnect: false
         * });
         *
         * socket.connect();
         */
        connect() {
            if (this.connected)
                return this;
            this.subEvents();
            if (!this.io["_reconnecting"])
                this.io.open(); // ensure open
            if ("open" === this.io._readyState)
                this.onopen();
            return this;
        }
        /**
         * Alias for {@link connect()}.
         */
        open() {
            return this.connect();
        }
        /**
         * Sends a `message` event.
         *
         * This method mimics the WebSocket.send() method.
         *
         * @see https://developer.mozilla.org/en-US/docs/Web/API/WebSocket/send
         *
         * @example
         * socket.send("hello");
         *
         * // this is equivalent to
         * socket.emit("message", "hello");
         *
         * @return self
         */
        send(...args) {
            args.unshift("message");
            this.emit.apply(this, args);
            return this;
        }
        /**
         * Override `emit`.
         * If the event is in `events`, it's emitted normally.
         *
         * @example
         * socket.emit("hello", "world");
         *
         * // all serializable datastructures are supported (no need to call JSON.stringify)
         * socket.emit("hello", 1, "2", { 3: ["4"], 5: Uint8Array.from([6]) });
         *
         * // with an acknowledgement from the server
         * socket.emit("hello", "world", (val) => {
         *   // ...
         * });
         *
         * @return self
         */
        emit(ev, ...args) {
            if (RESERVED_EVENTS.hasOwnProperty(ev)) {
                throw new Error('"' + ev.toString() + '" is a reserved event name');
            }
            args.unshift(ev);
            if (this._opts.retries && !this.flags.fromQueue && !this.flags.volatile) {
                this._addToQueue(args);
                return this;
            }
            const packet = {
                type: PacketType.EVENT,
                data: args,
            };
            packet.options = {};
            packet.options.compress = this.flags.compress !== false;
            // event ack callback
            if ("function" === typeof args[args.length - 1]) {
                const id = this.ids++;
                const ack = args.pop();
                this._registerAckCallback(id, ack);
                packet.id = id;
            }
            const isTransportWritable = this.io.engine &&
                this.io.engine.transport &&
                this.io.engine.transport.writable;
            const discardPacket = this.flags.volatile && (!isTransportWritable || !this.connected);
            if (discardPacket) ;
            else if (this.connected) {
                this.notifyOutgoingListeners(packet);
                this.packet(packet);
            }
            else {
                this.sendBuffer.push(packet);
            }
            this.flags = {};
            return this;
        }
        /**
         * @private
         */
        _registerAckCallback(id, ack) {
            var _a;
            const timeout = (_a = this.flags.timeout) !== null && _a !== void 0 ? _a : this._opts.ackTimeout;
            if (timeout === undefined) {
                this.acks[id] = ack;
                return;
            }
            // @ts-ignore
            const timer = this.io.setTimeoutFn(() => {
                delete this.acks[id];
                for (let i = 0; i < this.sendBuffer.length; i++) {
                    if (this.sendBuffer[i].id === id) {
                        this.sendBuffer.splice(i, 1);
                    }
                }
                ack.call(this, new Error("operation has timed out"));
            }, timeout);
            this.acks[id] = (...args) => {
                // @ts-ignore
                this.io.clearTimeoutFn(timer);
                ack.apply(this, [null, ...args]);
            };
        }
        /**
         * Emits an event and waits for an acknowledgement
         *
         * @example
         * // without timeout
         * const response = await socket.emitWithAck("hello", "world");
         *
         * // with a specific timeout
         * try {
         *   const response = await socket.timeout(1000).emitWithAck("hello", "world");
         * } catch (err) {
         *   // the server did not acknowledge the event in the given delay
         * }
         *
         * @return a Promise that will be fulfilled when the server acknowledges the event
         */
        emitWithAck(ev, ...args) {
            // the timeout flag is optional
            const withErr = this.flags.timeout !== undefined || this._opts.ackTimeout !== undefined;
            return new Promise((resolve, reject) => {
                args.push((arg1, arg2) => {
                    if (withErr) {
                        return arg1 ? reject(arg1) : resolve(arg2);
                    }
                    else {
                        return resolve(arg1);
                    }
                });
                this.emit(ev, ...args);
            });
        }
        /**
         * Add the packet to the queue.
         * @param args
         * @private
         */
        _addToQueue(args) {
            let ack;
            if (typeof args[args.length - 1] === "function") {
                ack = args.pop();
            }
            const packet = {
                id: this._queueSeq++,
                tryCount: 0,
                pending: false,
                args,
                flags: Object.assign({ fromQueue: true }, this.flags),
            };
            args.push((err, ...responseArgs) => {
                if (packet !== this._queue[0]) {
                    // the packet has already been acknowledged
                    return;
                }
                const hasError = err !== null;
                if (hasError) {
                    if (packet.tryCount > this._opts.retries) {
                        this._queue.shift();
                        if (ack) {
                            ack(err);
                        }
                    }
                }
                else {
                    this._queue.shift();
                    if (ack) {
                        ack(null, ...responseArgs);
                    }
                }
                packet.pending = false;
                return this._drainQueue();
            });
            this._queue.push(packet);
            this._drainQueue();
        }
        /**
         * Send the first packet of the queue, and wait for an acknowledgement from the server.
         * @param force - whether to resend a packet that has not been acknowledged yet
         *
         * @private
         */
        _drainQueue(force = false) {
            if (!this.connected || this._queue.length === 0) {
                return;
            }
            const packet = this._queue[0];
            if (packet.pending && !force) {
                return;
            }
            packet.pending = true;
            packet.tryCount++;
            this.flags = packet.flags;
            this.emit.apply(this, packet.args);
        }
        /**
         * Sends a packet.
         *
         * @param packet
         * @private
         */
        packet(packet) {
            packet.nsp = this.nsp;
            this.io._packet(packet);
        }
        /**
         * Called upon engine `open`.
         *
         * @private
         */
        onopen() {
            if (typeof this.auth == "function") {
                this.auth((data) => {
                    this._sendConnectPacket(data);
                });
            }
            else {
                this._sendConnectPacket(this.auth);
            }
        }
        /**
         * Sends a CONNECT packet to initiate the Socket.IO session.
         *
         * @param data
         * @private
         */
        _sendConnectPacket(data) {
            this.packet({
                type: PacketType.CONNECT,
                data: this._pid
                    ? Object.assign({ pid: this._pid, offset: this._lastOffset }, data)
                    : data,
            });
        }
        /**
         * Called upon engine or manager `error`.
         *
         * @param err
         * @private
         */
        onerror(err) {
            if (!this.connected) {
                this.emitReserved("connect_error", err);
            }
        }
        /**
         * Called upon engine `close`.
         *
         * @param reason
         * @param description
         * @private
         */
        onclose(reason, description) {
            this.connected = false;
            delete this.id;
            this.emitReserved("disconnect", reason, description);
        }
        /**
         * Called with socket packet.
         *
         * @param packet
         * @private
         */
        onpacket(packet) {
            const sameNamespace = packet.nsp === this.nsp;
            if (!sameNamespace)
                return;
            switch (packet.type) {
                case PacketType.CONNECT:
                    if (packet.data && packet.data.sid) {
                        this.onconnect(packet.data.sid, packet.data.pid);
                    }
                    else {
                        this.emitReserved("connect_error", new Error("It seems you are trying to reach a Socket.IO server in v2.x with a v3.x client, but they are not compatible (more information here: https://socket.io/docs/v3/migrating-from-2-x-to-3-0/)"));
                    }
                    break;
                case PacketType.EVENT:
                case PacketType.BINARY_EVENT:
                    this.onevent(packet);
                    break;
                case PacketType.ACK:
                case PacketType.BINARY_ACK:
                    this.onack(packet);
                    break;
                case PacketType.DISCONNECT:
                    this.ondisconnect();
                    break;
                case PacketType.CONNECT_ERROR:
                    this.destroy();
                    const err = new Error(packet.data.message);
                    // @ts-ignore
                    err.data = packet.data.data;
                    this.emitReserved("connect_error", err);
                    break;
            }
        }
        /**
         * Called upon a server event.
         *
         * @param packet
         * @private
         */
        onevent(packet) {
            const args = packet.data || [];
            if (null != packet.id) {
                args.push(this.ack(packet.id));
            }
            if (this.connected) {
                this.emitEvent(args);
            }
            else {
                this.receiveBuffer.push(Object.freeze(args));
            }
        }
        emitEvent(args) {
            if (this._anyListeners && this._anyListeners.length) {
                const listeners = this._anyListeners.slice();
                for (const listener of listeners) {
                    listener.apply(this, args);
                }
            }
            super.emit.apply(this, args);
            if (this._pid && args.length && typeof args[args.length - 1] === "string") {
                this._lastOffset = args[args.length - 1];
            }
        }
        /**
         * Produces an ack callback to emit with an event.
         *
         * @private
         */
        ack(id) {
            const self = this;
            let sent = false;
            return function (...args) {
                // prevent double callbacks
                if (sent)
                    return;
                sent = true;
                self.packet({
                    type: PacketType.ACK,
                    id: id,
                    data: args,
                });
            };
        }
        /**
         * Called upon a server acknowlegement.
         *
         * @param packet
         * @private
         */
        onack(packet) {
            const ack = this.acks[packet.id];
            if ("function" === typeof ack) {
                ack.apply(this, packet.data);
                delete this.acks[packet.id];
            }
        }
        /**
         * Called upon server connect.
         *
         * @private
         */
        onconnect(id, pid) {
            this.id = id;
            this.recovered = pid && this._pid === pid;
            this._pid = pid; // defined only if connection state recovery is enabled
            this.connected = true;
            this.emitBuffered();
            this.emitReserved("connect");
            this._drainQueue(true);
        }
        /**
         * Emit buffered events (received and emitted).
         *
         * @private
         */
        emitBuffered() {
            this.receiveBuffer.forEach((args) => this.emitEvent(args));
            this.receiveBuffer = [];
            this.sendBuffer.forEach((packet) => {
                this.notifyOutgoingListeners(packet);
                this.packet(packet);
            });
            this.sendBuffer = [];
        }
        /**
         * Called upon server disconnect.
         *
         * @private
         */
        ondisconnect() {
            this.destroy();
            this.onclose("io server disconnect");
        }
        /**
         * Called upon forced client/server side disconnections,
         * this method ensures the manager stops tracking us and
         * that reconnections don't get triggered for this.
         *
         * @private
         */
        destroy() {
            if (this.subs) {
                // clean subscriptions to avoid reconnections
                this.subs.forEach((subDestroy) => subDestroy());
                this.subs = undefined;
            }
            this.io["_destroy"](this);
        }
        /**
         * Disconnects the socket manually. In that case, the socket will not try to reconnect.
         *
         * If this is the last active Socket instance of the {@link Manager}, the low-level connection will be closed.
         *
         * @example
         * const socket = io();
         *
         * socket.on("disconnect", (reason) => {
         *   // console.log(reason); prints "io client disconnect"
         * });
         *
         * socket.disconnect();
         *
         * @return self
         */
        disconnect() {
            if (this.connected) {
                this.packet({ type: PacketType.DISCONNECT });
            }
            // remove socket from pool
            this.destroy();
            if (this.connected) {
                // fire events
                this.onclose("io client disconnect");
            }
            return this;
        }
        /**
         * Alias for {@link disconnect()}.
         *
         * @return self
         */
        close() {
            return this.disconnect();
        }
        /**
         * Sets the compress flag.
         *
         * @example
         * socket.compress(false).emit("hello");
         *
         * @param compress - if `true`, compresses the sending data
         * @return self
         */
        compress(compress) {
            this.flags.compress = compress;
            return this;
        }
        /**
         * Sets a modifier for a subsequent event emission that the event message will be dropped when this socket is not
         * ready to send messages.
         *
         * @example
         * socket.volatile.emit("hello"); // the server may or may not receive it
         *
         * @returns self
         */
        get volatile() {
            this.flags.volatile = true;
            return this;
        }
        /**
         * Sets a modifier for a subsequent event emission that the callback will be called with an error when the
         * given number of milliseconds have elapsed without an acknowledgement from the server:
         *
         * @example
         * socket.timeout(5000).emit("my-event", (err) => {
         *   if (err) {
         *     // the server did not acknowledge the event in the given delay
         *   }
         * });
         *
         * @returns self
         */
        timeout(timeout) {
            this.flags.timeout = timeout;
            return this;
        }
        /**
         * Adds a listener that will be fired when any event is emitted. The event name is passed as the first argument to the
         * callback.
         *
         * @example
         * socket.onAny((event, ...args) => {
         *   console.log(`got ${event}`);
         * });
         *
         * @param listener
         */
        onAny(listener) {
            this._anyListeners = this._anyListeners || [];
            this._anyListeners.push(listener);
            return this;
        }
        /**
         * Adds a listener that will be fired when any event is emitted. The event name is passed as the first argument to the
         * callback. The listener is added to the beginning of the listeners array.
         *
         * @example
         * socket.prependAny((event, ...args) => {
         *   console.log(`got event ${event}`);
         * });
         *
         * @param listener
         */
        prependAny(listener) {
            this._anyListeners = this._anyListeners || [];
            this._anyListeners.unshift(listener);
            return this;
        }
        /**
         * Removes the listener that will be fired when any event is emitted.
         *
         * @example
         * const catchAllListener = (event, ...args) => {
         *   console.log(`got event ${event}`);
         * }
         *
         * socket.onAny(catchAllListener);
         *
         * // remove a specific listener
         * socket.offAny(catchAllListener);
         *
         * // or remove all listeners
         * socket.offAny();
         *
         * @param listener
         */
        offAny(listener) {
            if (!this._anyListeners) {
                return this;
            }
            if (listener) {
                const listeners = this._anyListeners;
                for (let i = 0; i < listeners.length; i++) {
                    if (listener === listeners[i]) {
                        listeners.splice(i, 1);
                        return this;
                    }
                }
            }
            else {
                this._anyListeners = [];
            }
            return this;
        }
        /**
         * Returns an array of listeners that are listening for any event that is specified. This array can be manipulated,
         * e.g. to remove listeners.
         */
        listenersAny() {
            return this._anyListeners || [];
        }
        /**
         * Adds a listener that will be fired when any event is emitted. The event name is passed as the first argument to the
         * callback.
         *
         * Note: acknowledgements sent to the server are not included.
         *
         * @example
         * socket.onAnyOutgoing((event, ...args) => {
         *   console.log(`sent event ${event}`);
         * });
         *
         * @param listener
         */
        onAnyOutgoing(listener) {
            this._anyOutgoingListeners = this._anyOutgoingListeners || [];
            this._anyOutgoingListeners.push(listener);
            return this;
        }
        /**
         * Adds a listener that will be fired when any event is emitted. The event name is passed as the first argument to the
         * callback. The listener is added to the beginning of the listeners array.
         *
         * Note: acknowledgements sent to the server are not included.
         *
         * @example
         * socket.prependAnyOutgoing((event, ...args) => {
         *   console.log(`sent event ${event}`);
         * });
         *
         * @param listener
         */
        prependAnyOutgoing(listener) {
            this._anyOutgoingListeners = this._anyOutgoingListeners || [];
            this._anyOutgoingListeners.unshift(listener);
            return this;
        }
        /**
         * Removes the listener that will be fired when any event is emitted.
         *
         * @example
         * const catchAllListener = (event, ...args) => {
         *   console.log(`sent event ${event}`);
         * }
         *
         * socket.onAnyOutgoing(catchAllListener);
         *
         * // remove a specific listener
         * socket.offAnyOutgoing(catchAllListener);
         *
         * // or remove all listeners
         * socket.offAnyOutgoing();
         *
         * @param [listener] - the catch-all listener (optional)
         */
        offAnyOutgoing(listener) {
            if (!this._anyOutgoingListeners) {
                return this;
            }
            if (listener) {
                const listeners = this._anyOutgoingListeners;
                for (let i = 0; i < listeners.length; i++) {
                    if (listener === listeners[i]) {
                        listeners.splice(i, 1);
                        return this;
                    }
                }
            }
            else {
                this._anyOutgoingListeners = [];
            }
            return this;
        }
        /**
         * Returns an array of listeners that are listening for any event that is specified. This array can be manipulated,
         * e.g. to remove listeners.
         */
        listenersAnyOutgoing() {
            return this._anyOutgoingListeners || [];
        }
        /**
         * Notify the listeners for each packet sent
         *
         * @param packet
         *
         * @private
         */
        notifyOutgoingListeners(packet) {
            if (this._anyOutgoingListeners && this._anyOutgoingListeners.length) {
                const listeners = this._anyOutgoingListeners.slice();
                for (const listener of listeners) {
                    listener.apply(this, packet.data);
                }
            }
        }
    }

    /**
     * Initialize backoff timer with `opts`.
     *
     * - `min` initial timeout in milliseconds [100]
     * - `max` max timeout [10000]
     * - `jitter` [0]
     * - `factor` [2]
     *
     * @param {Object} opts
     * @api public
     */
    function Backoff(opts) {
        opts = opts || {};
        this.ms = opts.min || 100;
        this.max = opts.max || 10000;
        this.factor = opts.factor || 2;
        this.jitter = opts.jitter > 0 && opts.jitter <= 1 ? opts.jitter : 0;
        this.attempts = 0;
    }
    /**
     * Return the backoff duration.
     *
     * @return {Number}
     * @api public
     */
    Backoff.prototype.duration = function () {
        var ms = this.ms * Math.pow(this.factor, this.attempts++);
        if (this.jitter) {
            var rand = Math.random();
            var deviation = Math.floor(rand * this.jitter * ms);
            ms = (Math.floor(rand * 10) & 1) == 0 ? ms - deviation : ms + deviation;
        }
        return Math.min(ms, this.max) | 0;
    };
    /**
     * Reset the number of attempts.
     *
     * @api public
     */
    Backoff.prototype.reset = function () {
        this.attempts = 0;
    };
    /**
     * Set the minimum duration
     *
     * @api public
     */
    Backoff.prototype.setMin = function (min) {
        this.ms = min;
    };
    /**
     * Set the maximum duration
     *
     * @api public
     */
    Backoff.prototype.setMax = function (max) {
        this.max = max;
    };
    /**
     * Set the jitter
     *
     * @api public
     */
    Backoff.prototype.setJitter = function (jitter) {
        this.jitter = jitter;
    };

    class Manager extends Emitter {
        constructor(uri, opts) {
            var _a;
            super();
            this.nsps = {};
            this.subs = [];
            if (uri && "object" === typeof uri) {
                opts = uri;
                uri = undefined;
            }
            opts = opts || {};
            opts.path = opts.path || "/socket.io";
            this.opts = opts;
            installTimerFunctions(this, opts);
            this.reconnection(opts.reconnection !== false);
            this.reconnectionAttempts(opts.reconnectionAttempts || Infinity);
            this.reconnectionDelay(opts.reconnectionDelay || 1000);
            this.reconnectionDelayMax(opts.reconnectionDelayMax || 5000);
            this.randomizationFactor((_a = opts.randomizationFactor) !== null && _a !== void 0 ? _a : 0.5);
            this.backoff = new Backoff({
                min: this.reconnectionDelay(),
                max: this.reconnectionDelayMax(),
                jitter: this.randomizationFactor(),
            });
            this.timeout(null == opts.timeout ? 20000 : opts.timeout);
            this._readyState = "closed";
            this.uri = uri;
            const _parser = opts.parser || parser;
            this.encoder = new _parser.Encoder();
            this.decoder = new _parser.Decoder();
            this._autoConnect = opts.autoConnect !== false;
            if (this._autoConnect)
                this.open();
        }
        reconnection(v) {
            if (!arguments.length)
                return this._reconnection;
            this._reconnection = !!v;
            return this;
        }
        reconnectionAttempts(v) {
            if (v === undefined)
                return this._reconnectionAttempts;
            this._reconnectionAttempts = v;
            return this;
        }
        reconnectionDelay(v) {
            var _a;
            if (v === undefined)
                return this._reconnectionDelay;
            this._reconnectionDelay = v;
            (_a = this.backoff) === null || _a === void 0 ? void 0 : _a.setMin(v);
            return this;
        }
        randomizationFactor(v) {
            var _a;
            if (v === undefined)
                return this._randomizationFactor;
            this._randomizationFactor = v;
            (_a = this.backoff) === null || _a === void 0 ? void 0 : _a.setJitter(v);
            return this;
        }
        reconnectionDelayMax(v) {
            var _a;
            if (v === undefined)
                return this._reconnectionDelayMax;
            this._reconnectionDelayMax = v;
            (_a = this.backoff) === null || _a === void 0 ? void 0 : _a.setMax(v);
            return this;
        }
        timeout(v) {
            if (!arguments.length)
                return this._timeout;
            this._timeout = v;
            return this;
        }
        /**
         * Starts trying to reconnect if reconnection is enabled and we have not
         * started reconnecting yet
         *
         * @private
         */
        maybeReconnectOnOpen() {
            // Only try to reconnect if it's the first time we're connecting
            if (!this._reconnecting &&
                this._reconnection &&
                this.backoff.attempts === 0) {
                // keeps reconnection from firing twice for the same reconnection loop
                this.reconnect();
            }
        }
        /**
         * Sets the current transport `socket`.
         *
         * @param {Function} fn - optional, callback
         * @return self
         * @public
         */
        open(fn) {
            if (~this._readyState.indexOf("open"))
                return this;
            this.engine = new Socket$1(this.uri, this.opts);
            const socket = this.engine;
            const self = this;
            this._readyState = "opening";
            this.skipReconnect = false;
            // emit `open`
            const openSubDestroy = on(socket, "open", function () {
                self.onopen();
                fn && fn();
            });
            // emit `error`
            const errorSub = on(socket, "error", (err) => {
                self.cleanup();
                self._readyState = "closed";
                this.emitReserved("error", err);
                if (fn) {
                    fn(err);
                }
                else {
                    // Only do this if there is no fn to handle the error
                    self.maybeReconnectOnOpen();
                }
            });
            if (false !== this._timeout) {
                const timeout = this._timeout;
                if (timeout === 0) {
                    openSubDestroy(); // prevents a race condition with the 'open' event
                }
                // set timer
                const timer = this.setTimeoutFn(() => {
                    openSubDestroy();
                    socket.close();
                    // @ts-ignore
                    socket.emit("error", new Error("timeout"));
                }, timeout);
                if (this.opts.autoUnref) {
                    timer.unref();
                }
                this.subs.push(function subDestroy() {
                    clearTimeout(timer);
                });
            }
            this.subs.push(openSubDestroy);
            this.subs.push(errorSub);
            return this;
        }
        /**
         * Alias for open()
         *
         * @return self
         * @public
         */
        connect(fn) {
            return this.open(fn);
        }
        /**
         * Called upon transport open.
         *
         * @private
         */
        onopen() {
            // clear old subs
            this.cleanup();
            // mark as open
            this._readyState = "open";
            this.emitReserved("open");
            // add new subs
            const socket = this.engine;
            this.subs.push(on(socket, "ping", this.onping.bind(this)), on(socket, "data", this.ondata.bind(this)), on(socket, "error", this.onerror.bind(this)), on(socket, "close", this.onclose.bind(this)), on(this.decoder, "decoded", this.ondecoded.bind(this)));
        }
        /**
         * Called upon a ping.
         *
         * @private
         */
        onping() {
            this.emitReserved("ping");
        }
        /**
         * Called with data.
         *
         * @private
         */
        ondata(data) {
            try {
                this.decoder.add(data);
            }
            catch (e) {
                this.onclose("parse error", e);
            }
        }
        /**
         * Called when parser fully decodes a packet.
         *
         * @private
         */
        ondecoded(packet) {
            // the nextTick call prevents an exception in a user-provided event listener from triggering a disconnection due to a "parse error"
            nextTick(() => {
                this.emitReserved("packet", packet);
            }, this.setTimeoutFn);
        }
        /**
         * Called upon socket error.
         *
         * @private
         */
        onerror(err) {
            this.emitReserved("error", err);
        }
        /**
         * Creates a new socket for the given `nsp`.
         *
         * @return {Socket}
         * @public
         */
        socket(nsp, opts) {
            let socket = this.nsps[nsp];
            if (!socket) {
                socket = new Socket(this, nsp, opts);
                this.nsps[nsp] = socket;
            }
            else if (this._autoConnect && !socket.active) {
                socket.connect();
            }
            return socket;
        }
        /**
         * Called upon a socket close.
         *
         * @param socket
         * @private
         */
        _destroy(socket) {
            const nsps = Object.keys(this.nsps);
            for (const nsp of nsps) {
                const socket = this.nsps[nsp];
                if (socket.active) {
                    return;
                }
            }
            this._close();
        }
        /**
         * Writes a packet.
         *
         * @param packet
         * @private
         */
        _packet(packet) {
            const encodedPackets = this.encoder.encode(packet);
            for (let i = 0; i < encodedPackets.length; i++) {
                this.engine.write(encodedPackets[i], packet.options);
            }
        }
        /**
         * Clean up transport subscriptions and packet buffer.
         *
         * @private
         */
        cleanup() {
            this.subs.forEach((subDestroy) => subDestroy());
            this.subs.length = 0;
            this.decoder.destroy();
        }
        /**
         * Close the current socket.
         *
         * @private
         */
        _close() {
            this.skipReconnect = true;
            this._reconnecting = false;
            this.onclose("forced close");
            if (this.engine)
                this.engine.close();
        }
        /**
         * Alias for close()
         *
         * @private
         */
        disconnect() {
            return this._close();
        }
        /**
         * Called upon engine close.
         *
         * @private
         */
        onclose(reason, description) {
            this.cleanup();
            this.backoff.reset();
            this._readyState = "closed";
            this.emitReserved("close", reason, description);
            if (this._reconnection && !this.skipReconnect) {
                this.reconnect();
            }
        }
        /**
         * Attempt a reconnection.
         *
         * @private
         */
        reconnect() {
            if (this._reconnecting || this.skipReconnect)
                return this;
            const self = this;
            if (this.backoff.attempts >= this._reconnectionAttempts) {
                this.backoff.reset();
                this.emitReserved("reconnect_failed");
                this._reconnecting = false;
            }
            else {
                const delay = this.backoff.duration();
                this._reconnecting = true;
                const timer = this.setTimeoutFn(() => {
                    if (self.skipReconnect)
                        return;
                    this.emitReserved("reconnect_attempt", self.backoff.attempts);
                    // check again for the case socket closed in above events
                    if (self.skipReconnect)
                        return;
                    self.open((err) => {
                        if (err) {
                            self._reconnecting = false;
                            self.reconnect();
                            this.emitReserved("reconnect_error", err);
                        }
                        else {
                            self.onreconnect();
                        }
                    });
                }, delay);
                if (this.opts.autoUnref) {
                    timer.unref();
                }
                this.subs.push(function subDestroy() {
                    clearTimeout(timer);
                });
            }
        }
        /**
         * Called upon successful reconnect.
         *
         * @private
         */
        onreconnect() {
            const attempt = this.backoff.attempts;
            this._reconnecting = false;
            this.backoff.reset();
            this.emitReserved("reconnect", attempt);
        }
    }

    /**
     * Managers cache.
     */
    const cache = {};
    function lookup(uri, opts) {
        if (typeof uri === "object") {
            opts = uri;
            uri = undefined;
        }
        opts = opts || {};
        const parsed = url(uri, opts.path || "/socket.io");
        const source = parsed.source;
        const id = parsed.id;
        const path = parsed.path;
        const sameNamespace = cache[id] && path in cache[id]["nsps"];
        const newConnection = opts.forceNew ||
            opts["force new connection"] ||
            false === opts.multiplex ||
            sameNamespace;
        let io;
        if (newConnection) {
            io = new Manager(source, opts);
        }
        else {
            if (!cache[id]) {
                cache[id] = new Manager(source, opts);
            }
            io = cache[id];
        }
        if (parsed.query && !opts.query) {
            opts.query = parsed.queryKey;
        }
        return io.socket(parsed.path, opts);
    }
    // so that "lookup" can be used both as a function (e.g. `io(...)`) and as a
    // namespace (e.g. `io.connect(...)`), for backward compatibility
    Object.assign(lookup, {
        Manager,
        Socket,
        io: lookup,
        connect: lookup,
    });

    const rooms$1 = writable([]);

    let socket$1 = {chat: null, game: null};
    let socketData;

    async function initializeSocket(data) {
      socketData = await data;
      if (!socketData)
      	return;
      socket$1.chat = lookup(hostname+':3000/chat', {path: '/chatsockets'});//, auth: {token: }});
      socket$1.chat.emit('whoAmI', socketData.id);

      socket$1.game = lookup(hostname+':3000/pong', {path: '/pongsockets'});//, auth: {token: }});
      reloadRooms();
      defineSocketEvents();
      defineGameSocketEvents();
    //   await new Promise(r => setTimeout(r, 3000)); //TEST
    //   socket.chat.disconnect();
    }

    async function reloadRooms() {
    	let loadedRooms = await fetchData();
    	rooms$1.set(loadedRooms);
    	connectToRooms();
    }

    function getSocket() {
      return socket$1;
    }


    let defineSocketEvents = () =>
    {
    	socket$1.chat.on('serverAlertToChat', newMessage);
    	// socket.chat.on('clientRefreshRooms', reloadRooms);
    	
    };

    let deleteSocketEvents = () =>
    {
    	socket$1.chat.off('serverAlertToChat', newMessage);
    };

    let defineGameSocketEvents = () =>
    {
    	socket$1.game.on('testSeverToClient', (data) => {
    		console.log(data);
    	});

    	socket$1.game.on('mvtpad', (data) => {

    	});
    };
    /*
    export let deleteGameSocketEvents = () =>
    {
    	socket.chat.off('testSeverToClient');
    }
    */
    let newMessage = (msg) =>
    {
    	let trythis = get_store_value(rooms$1);
    	trythis = trythis.map((item) => 
    	{
    		if (item.roomId == msg.channel)
    			return { ...item, newMsgCount: item.newMsgCount + 1 };
    		return (item);
    	});
    	rooms$1.set(trythis);
    };



    let connectToRooms = () => {
    	get_store_value(rooms$1).forEach(room => {
    		socket$1.chat.emit('joinChannel', room.roomId);
    	});
    };

    async function fetchData() {
    	let data = socketData;
    	let curr_rooms = get_store_value(rooms$1);
    	try {
    		const response = await fetch(`http://${hostname}:3000/chat/${data.id42}`);
    		let tmp_rooms = await response.json();
    		tmp_rooms.forEach((el) =>
    		{
    			if (curr_rooms.find((room) => (room.roomId == el.roomId)) == undefined)
    				curr_rooms = [...curr_rooms, { ...el, newMsgCount: 0}];
    		});
    		return curr_rooms;
    	}
    	catch (error) {
    		console.error(error);
    	}
    }

    /* src/shared/Tabs.svelte generated by Svelte v3.59.1 */
    const file$b = "src/shared/Tabs.svelte";

    function create_fragment$b(ctx) {
    	let rankmodal;
    	let t0;
    	let flmodal;
    	let t1;
    	let nav;
    	let a0;
    	let t3;
    	let a1;
    	let t5;
    	let a2;
    	let t6;
    	let t7;
    	let a3;
    	let t9;
    	let center;
    	let button0;
    	let t11;
    	let button1;
    	let t13;
    	let button2;
    	let current;
    	let mounted;
    	let dispose;

    	rankmodal = new Ranking({
    			props: { ranksTab: /*ranksTab*/ ctx[2] },
    			$$inline: true
    		});

    	rankmodal.$on("click", /*click_handler*/ ctx[9]);

    	flmodal = new FriendList({
    			props: {
    				flTab: /*flTab*/ ctx[3],
    				id: /*id*/ ctx[0]
    			},
    			$$inline: true
    		});

    	flmodal.$on("click", /*click_handler_1*/ ctx[10]);

    	const block = {
    		c: function create() {
    			create_component(rankmodal.$$.fragment);
    			t0 = space();
    			create_component(flmodal.$$.fragment);
    			t1 = space();
    			nav = element("nav");
    			a0 = element("a");
    			a0.textContent = "DashBoard";
    			t3 = space();
    			a1 = element("a");
    			a1.textContent = "Game";
    			t5 = space();
    			a2 = element("a");
    			t6 = text("Chat");
    			t7 = space();
    			a3 = element("a");
    			a3.textContent = "Room";
    			t9 = space();
    			center = element("center");
    			button0 = element("button");
    			button0.textContent = "Friend List";
    			t11 = space();
    			button1 = element("button");
    			button1.textContent = "Ranking";
    			t13 = space();
    			button2 = element("button");
    			button2.textContent = "Match history";
    			attr_dev(a0, "href", "/");
    			attr_dev(a0, "class", "svelte-1e6wrzh");
    			toggle_class(a0, "active", /*$page_shown*/ ctx[4] == "/");
    			add_location(a0, file$b, 43, 1, 866);
    			attr_dev(a1, "href", "game");
    			attr_dev(a1, "class", "svelte-1e6wrzh");
    			toggle_class(a1, "active", /*$page_shown*/ ctx[4] == "game");
    			add_location(a1, file$b, 44, 1, 963);
    			attr_dev(a2, "href", "chat");
    			attr_dev(a2, "number", /*newMessage*/ ctx[1]);
    			attr_dev(a2, "class", "svelte-1e6wrzh");
    			toggle_class(a2, "active", /*$page_shown*/ ctx[4] == "chat");
    			toggle_class(a2, "newMessage", /*newMessage*/ ctx[1]);
    			add_location(a2, file$b, 45, 1, 1061);
    			attr_dev(a3, "href", "room");
    			attr_dev(a3, "class", "svelte-1e6wrzh");
    			toggle_class(a3, "active", /*$page_shown*/ ctx[4] == "room");
    			add_location(a3, file$b, 46, 1, 1209);
    			attr_dev(nav, "class", "tabs svelte-1e6wrzh");
    			add_location(nav, file$b, 42, 0, 846);
    			attr_dev(button0, "class", "round-button svelte-1e6wrzh");
    			add_location(button0, file$b, 49, 1, 1324);
    			attr_dev(button1, "class", "round-button svelte-1e6wrzh");
    			add_location(button1, file$b, 50, 1, 1406);
    			attr_dev(button2, "class", "round-button svelte-1e6wrzh");
    			add_location(button2, file$b, 51, 1, 1487);
    			add_location(center, file$b, 48, 0, 1314);
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			mount_component(rankmodal, target, anchor);
    			insert_dev(target, t0, anchor);
    			mount_component(flmodal, target, anchor);
    			insert_dev(target, t1, anchor);
    			insert_dev(target, nav, anchor);
    			append_dev(nav, a0);
    			append_dev(nav, t3);
    			append_dev(nav, a1);
    			append_dev(nav, t5);
    			append_dev(nav, a2);
    			append_dev(a2, t6);
    			append_dev(nav, t7);
    			append_dev(nav, a3);
    			insert_dev(target, t9, anchor);
    			insert_dev(target, center, anchor);
    			append_dev(center, button0);
    			append_dev(center, t11);
    			append_dev(center, button1);
    			append_dev(center, t13);
    			append_dev(center, button2);
    			current = true;

    			if (!mounted) {
    				dispose = [
    					listen_dev(a0, "click", prevent_default(/*show_page*/ ctx[5]), false, true, false, false),
    					listen_dev(a1, "click", prevent_default(/*show_page*/ ctx[5]), false, true, false, false),
    					listen_dev(a2, "click", prevent_default(/*show_page*/ ctx[5]), false, true, false, false),
    					listen_dev(a3, "click", prevent_default(/*show_page*/ ctx[5]), false, true, false, false),
    					listen_dev(button0, "click", /*click_handler_2*/ ctx[11], false, false, false, false),
    					listen_dev(button1, "click", /*click_handler_3*/ ctx[12], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(ctx, [dirty]) {
    			const rankmodal_changes = {};
    			if (dirty & /*ranksTab*/ 4) rankmodal_changes.ranksTab = /*ranksTab*/ ctx[2];
    			rankmodal.$set(rankmodal_changes);
    			const flmodal_changes = {};
    			if (dirty & /*flTab*/ 8) flmodal_changes.flTab = /*flTab*/ ctx[3];
    			if (dirty & /*id*/ 1) flmodal_changes.id = /*id*/ ctx[0];
    			flmodal.$set(flmodal_changes);

    			if (!current || dirty & /*$page_shown*/ 16) {
    				toggle_class(a0, "active", /*$page_shown*/ ctx[4] == "/");
    			}

    			if (!current || dirty & /*$page_shown*/ 16) {
    				toggle_class(a1, "active", /*$page_shown*/ ctx[4] == "game");
    			}

    			if (!current || dirty & /*newMessage*/ 2) {
    				attr_dev(a2, "number", /*newMessage*/ ctx[1]);
    			}

    			if (!current || dirty & /*$page_shown*/ 16) {
    				toggle_class(a2, "active", /*$page_shown*/ ctx[4] == "chat");
    			}

    			if (!current || dirty & /*newMessage*/ 2) {
    				toggle_class(a2, "newMessage", /*newMessage*/ ctx[1]);
    			}

    			if (!current || dirty & /*$page_shown*/ 16) {
    				toggle_class(a3, "active", /*$page_shown*/ ctx[4] == "room");
    			}
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(rankmodal.$$.fragment, local);
    			transition_in(flmodal.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(rankmodal.$$.fragment, local);
    			transition_out(flmodal.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(rankmodal, detaching);
    			if (detaching) detach_dev(t0);
    			destroy_component(flmodal, detaching);
    			if (detaching) detach_dev(t1);
    			if (detaching) detach_dev(nav);
    			if (detaching) detach_dev(t9);
    			if (detaching) detach_dev(center);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$b.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$b($$self, $$props, $$invalidate) {
    	let $page_shown;
    	let $rooms;
    	validate_store(page_shown, 'page_shown');
    	component_subscribe($$self, page_shown, $$value => $$invalidate(4, $page_shown = $$value));
    	validate_store(rooms$1, 'rooms');
    	component_subscribe($$self, rooms$1, $$value => $$invalidate(8, $rooms = $$value));
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Tabs', slots, []);
    	const dispatch = createEventDispatcher();
    	let newMessage = 0;

    	const show_page = () => {
    		const url = event.target.getAttribute("href");
    		history.pushState({ "href_to_show": url }, '', url);
    		set_store_value(page_shown, $page_shown = url, $page_shown);
    	};

    	let { id } = $$props;
    	let ranksTab = false;
    	let flTab = false;

    	function toggleRanksTab() {
    		$$invalidate(2, ranksTab = !ranksTab);
    	}

    	function toggleFlTab() {
    		$$invalidate(3, flTab = !flTab);
    	}

    	$$self.$$.on_mount.push(function () {
    		if (id === undefined && !('id' in $$props || $$self.$$.bound[$$self.$$.props['id']])) {
    			console.warn("<Tabs> was created without expected prop 'id'");
    		}
    	});

    	const writable_props = ['id'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console.warn(`<Tabs> was created with unknown prop '${key}'`);
    	});

    	const click_handler = () => toggleRanksTab();
    	const click_handler_1 = () => toggleFlTab();
    	const click_handler_2 = () => toggleFlTab();
    	const click_handler_3 = () => toggleRanksTab();

    	$$self.$$set = $$props => {
    		if ('id' in $$props) $$invalidate(0, id = $$props.id);
    	};

    	$$self.$capture_state = () => ({
    		createEventDispatcher,
    		RankModal: Ranking,
    		FlModal: FriendList,
    		page_shown,
    		rooms: rooms$1,
    		dispatch,
    		newMessage,
    		show_page,
    		id,
    		ranksTab,
    		flTab,
    		toggleRanksTab,
    		toggleFlTab,
    		$page_shown,
    		$rooms
    	});

    	$$self.$inject_state = $$props => {
    		if ('newMessage' in $$props) $$invalidate(1, newMessage = $$props.newMessage);
    		if ('id' in $$props) $$invalidate(0, id = $$props.id);
    		if ('ranksTab' in $$props) $$invalidate(2, ranksTab = $$props.ranksTab);
    		if ('flTab' in $$props) $$invalidate(3, flTab = $$props.flTab);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	$$self.$$.update = () => {
    		if ($$self.$$.dirty & /*$rooms, newMessage*/ 258) {
    			{
    				$$invalidate(1, newMessage = 0);

    				$rooms.forEach(element => {
    					$$invalidate(1, newMessage += element.newMsgCount);
    				});
    			}
    		}
    	};

    	return [
    		id,
    		newMessage,
    		ranksTab,
    		flTab,
    		$page_shown,
    		show_page,
    		toggleRanksTab,
    		toggleFlTab,
    		$rooms,
    		click_handler,
    		click_handler_1,
    		click_handler_2,
    		click_handler_3
    	];
    }

    class Tabs extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$b, create_fragment$b, safe_not_equal, { id: 0 });

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Tabs",
    			options,
    			id: create_fragment$b.name
    		});
    	}

    	get id() {
    		throw new Error("<Tabs>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set id(value) {
    		throw new Error("<Tabs>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/component/dashboard/Update.svelte generated by Svelte v3.59.1 */

    const { console: console_1$7 } = globals;
    const file$a = "src/component/dashboard/Update.svelte";

    // (93:20) 
    function create_if_block_1$5(ctx) {
    	let div1;
    	let div0;
    	let h1;
    	let t1;
    	let t2;
    	let button;
    	let mounted;
    	let dispose;

    	function select_block_type_1(ctx, dirty) {
    		if (/*indexBadUpdate*/ ctx[2] === 1) return create_if_block_2$4;
    		if (/*indexBadUpdate*/ ctx[2] === 2) return create_if_block_3$4;
    		if (/*indexBadUpdate*/ ctx[2] === 3) return create_if_block_4$4;
    	}

    	let current_block_type = select_block_type_1(ctx);
    	let if_block = current_block_type && current_block_type(ctx);

    	const block = {
    		c: function create() {
    			div1 = element("div");
    			div0 = element("div");
    			h1 = element("h1");
    			h1.textContent = "sry something went wrong";
    			t1 = space();
    			if (if_block) if_block.c();
    			t2 = space();
    			button = element("button");
    			button.textContent = "close";
    			attr_dev(h1, "class", "svelte-nyjrp4");
    			add_location(h1, file$a, 96, 3, 1956);
    			add_location(button, file$a, 105, 3, 2220);
    			attr_dev(div0, "class", "modal svelte-nyjrp4");
    			add_location(div0, file$a, 95, 2, 1933);
    			attr_dev(div1, "class", "backdrop svelte-nyjrp4");
    			add_location(div1, file$a, 94, 1, 1882);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div1, anchor);
    			append_dev(div1, div0);
    			append_dev(div0, h1);
    			append_dev(div0, t1);
    			if (if_block) if_block.m(div0, null);
    			append_dev(div0, t2);
    			append_dev(div0, button);

    			if (!mounted) {
    				dispose = [
    					listen_dev(button, "click", /*click_handler_3*/ ctx[11], false, false, false, false),
    					listen_dev(div1, "click", self$1(/*click_handler_2*/ ctx[9]), false, false, false, false),
    					listen_dev(div1, "keypress", /*keypress_handler_1*/ ctx[10], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (current_block_type !== (current_block_type = select_block_type_1(ctx))) {
    				if (if_block) if_block.d(1);
    				if_block = current_block_type && current_block_type(ctx);

    				if (if_block) {
    					if_block.c();
    					if_block.m(div0, t2);
    				}
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div1);

    			if (if_block) {
    				if_block.d();
    			}

    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_1$5.name,
    		type: "if",
    		source: "(93:20) ",
    		ctx
    	});

    	return block;
    }

    // (72:0) {#if updatePop && !badUpdate}
    function create_if_block$7(ctx) {
    	let div3;
    	let div2;
    	let h1;
    	let t1;
    	let p;
    	let t3;
    	let label0;
    	let t5;
    	let div0;
    	let input0;
    	let t6;
    	let label1;
    	let t8;
    	let div1;
    	let input1;
    	let t9;
    	let button;
    	let mounted;
    	let dispose;

    	const block = {
    		c: function create() {
    			div3 = element("div");
    			div2 = element("div");
    			h1 = element("h1");
    			h1.textContent = "Update Profile";
    			t1 = space();
    			p = element("p");
    			p.textContent = "Change de peau";
    			t3 = space();
    			label0 = element("label");
    			label0.textContent = "What's your new name?";
    			t5 = space();
    			div0 = element("div");
    			input0 = element("input");
    			t6 = space();
    			label1 = element("label");
    			label1.textContent = "Select a File";
    			t8 = space();
    			div1 = element("div");
    			input1 = element("input");
    			t9 = space();
    			button = element("button");
    			button.textContent = "Validate";
    			attr_dev(h1, "class", "svelte-nyjrp4");
    			add_location(h1, file$a, 74, 3, 1398);
    			attr_dev(p, "class", "svelte-nyjrp4");
    			add_location(p, file$a, 75, 3, 1425);
    			attr_dev(label0, "for", "name upload");
    			attr_dev(label0, "class", "svelte-nyjrp4");
    			add_location(label0, file$a, 77, 3, 1451);
    			attr_dev(input0, "type", "text");
    			attr_dev(input0, "name", "name-upload");
    			attr_dev(input0, "id", "name-upload");
    			add_location(input0, file$a, 79, 4, 1548);
    			attr_dev(div0, "class", "file-input-container svelte-nyjrp4");
    			add_location(div0, file$a, 78, 3, 1509);
    			attr_dev(label1, "for", "file upload");
    			attr_dev(label1, "class", "svelte-nyjrp4");
    			add_location(label1, file$a, 82, 3, 1618);
    			attr_dev(input1, "type", "file");
    			attr_dev(input1, "name", "file-upload");
    			attr_dev(input1, "id", "file-upload");
    			add_location(input1, file$a, 84, 4, 1707);
    			attr_dev(div1, "class", "file-input-container svelte-nyjrp4");
    			add_location(div1, file$a, 83, 3, 1668);
    			add_location(button, file$a, 87, 3, 1777);
    			attr_dev(div2, "class", "modal svelte-nyjrp4");
    			add_location(div2, file$a, 73, 2, 1375);
    			attr_dev(div3, "class", "backdrop svelte-nyjrp4");
    			add_location(div3, file$a, 72, 1, 1324);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div3, anchor);
    			append_dev(div3, div2);
    			append_dev(div2, h1);
    			append_dev(div2, t1);
    			append_dev(div2, p);
    			append_dev(div2, t3);
    			append_dev(div2, label0);
    			append_dev(div2, t5);
    			append_dev(div2, div0);
    			append_dev(div0, input0);
    			append_dev(div2, t6);
    			append_dev(div2, label1);
    			append_dev(div2, t8);
    			append_dev(div2, div1);
    			append_dev(div1, input1);
    			append_dev(div2, t9);
    			append_dev(div2, button);

    			if (!mounted) {
    				dispose = [
    					listen_dev(button, "click", /*submitForm*/ ctx[3], false, false, false, false),
    					listen_dev(button, "click", self$1(/*click_handler_1*/ ctx[8]), false, false, false, false),
    					listen_dev(div3, "click", self$1(/*click_handler*/ ctx[6]), false, false, false, false),
    					listen_dev(div3, "keypress", /*keypress_handler*/ ctx[7], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div3);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block$7.name,
    		type: "if",
    		source: "(72:0) {#if updatePop && !badUpdate}",
    		ctx
    	});

    	return block;
    }

    // (102:34) 
    function create_if_block_4$4(ctx) {
    	let p0;
    	let t1;
    	let p1;

    	const block = {
    		c: function create() {
    			p0 = element("p");
    			p0.textContent = "neither name nor img";
    			t1 = space();
    			p1 = element("p");
    			p1.textContent = "nothing updated";
    			attr_dev(p0, "class", "svelte-nyjrp4");
    			add_location(p0, file$a, 102, 4, 2152);
    			attr_dev(p1, "class", "svelte-nyjrp4");
    			add_location(p1, file$a, 103, 4, 2185);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p0, anchor);
    			insert_dev(target, t1, anchor);
    			insert_dev(target, p1, anchor);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p0);
    			if (detaching) detach_dev(t1);
    			if (detaching) detach_dev(p1);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_4$4.name,
    		type: "if",
    		source: "(102:34) ",
    		ctx
    	});

    	return block;
    }

    // (100:34) 
    function create_if_block_3$4(ctx) {
    	let p;

    	const block = {
    		c: function create() {
    			p = element("p");
    			p.textContent = "name not updated";
    			attr_dev(p, "class", "svelte-nyjrp4");
    			add_location(p, file$a, 100, 4, 2089);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_3$4.name,
    		type: "if",
    		source: "(100:34) ",
    		ctx
    	});

    	return block;
    }

    // (98:3) {#if indexBadUpdate === 1}
    function create_if_block_2$4(ctx) {
    	let p;

    	const block = {
    		c: function create() {
    			p = element("p");
    			p.textContent = "img not updated";
    			attr_dev(p, "class", "svelte-nyjrp4");
    			add_location(p, file$a, 98, 4, 2024);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_2$4.name,
    		type: "if",
    		source: "(98:3) {#if indexBadUpdate === 1}",
    		ctx
    	});

    	return block;
    }

    function create_fragment$a(ctx) {
    	let if_block_anchor;

    	function select_block_type(ctx, dirty) {
    		if (/*updatePop*/ ctx[0] && !/*badUpdate*/ ctx[1]) return create_if_block$7;
    		if (/*badUpdate*/ ctx[1]) return create_if_block_1$5;
    	}

    	let current_block_type = select_block_type(ctx);
    	let if_block = current_block_type && current_block_type(ctx);

    	const block = {
    		c: function create() {
    			if (if_block) if_block.c();
    			if_block_anchor = empty$1();
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			if (if_block) if_block.m(target, anchor);
    			insert_dev(target, if_block_anchor, anchor);
    		},
    		p: function update(ctx, [dirty]) {
    			if (current_block_type === (current_block_type = select_block_type(ctx)) && if_block) {
    				if_block.p(ctx, dirty);
    			} else {
    				if (if_block) if_block.d(1);
    				if_block = current_block_type && current_block_type(ctx);

    				if (if_block) {
    					if_block.c();
    					if_block.m(if_block_anchor.parentNode, if_block_anchor);
    				}
    			}
    		},
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (if_block) {
    				if_block.d(detaching);
    			}

    			if (detaching) detach_dev(if_block_anchor);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$a.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$a($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Update', slots, []);
    	const dispatch = createEventDispatcher();
    	let { updatePop } = $$props;
    	let { id } = $$props;
    	let badUpdate = false;
    	let indexBadUpdate = 0;

    	async function submitForm() {
    		const nameInput = document.getElementById("name-upload");
    		const fileInput = document.getElementById("file-upload");
    		let data = new FormData();
    		data.append("file", fileInput.files[0]);

    		if (fileInput && fileInput.files && fileInput.files[0]) {
    			try {
    				const response = await fetch(`http://${hostname}:3000/dashboard/update/${id}`, { method: 'POST', body: data });

    				if (!response.ok) {
    					console.log('nop');
    					$$invalidate(2, indexBadUpdate += 1);
    					$$invalidate(1, badUpdate = true);
    				}
    			} catch(error) {
    				console.log(error);
    			}
    		}

    		if (nameInput) {
    			try {
    				const response = await fetch(`http://${hostname}:3000/dashboard/updateName/${id}`, { method: 'POST', body: nameInput.value });

    				if (!response.ok) {
    					console.log('nop2');
    					$$invalidate(2, indexBadUpdate += 2);
    					$$invalidate(1, badUpdate = true);
    				}
    			} catch(error) {
    				console.log(error);
    			}
    		}

    		dispatch('updated');
    	}

    	function closePopUp() {
    		$$invalidate(1, badUpdate = false);
    		$$invalidate(2, indexBadUpdate = 0);
    	}

    	$$self.$$.on_mount.push(function () {
    		if (updatePop === undefined && !('updatePop' in $$props || $$self.$$.bound[$$self.$$.props['updatePop']])) {
    			console_1$7.warn("<Update> was created without expected prop 'updatePop'");
    		}

    		if (id === undefined && !('id' in $$props || $$self.$$.bound[$$self.$$.props['id']])) {
    			console_1$7.warn("<Update> was created without expected prop 'id'");
    		}
    	});

    	const writable_props = ['updatePop', 'id'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console_1$7.warn(`<Update> was created with unknown prop '${key}'`);
    	});

    	function click_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	function keypress_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	function click_handler_1(event) {
    		bubble.call(this, $$self, event);
    	}

    	function click_handler_2(event) {
    		bubble.call(this, $$self, event);
    	}

    	function keypress_handler_1(event) {
    		bubble.call(this, $$self, event);
    	}

    	const click_handler_3 = () => closePopUp();

    	$$self.$$set = $$props => {
    		if ('updatePop' in $$props) $$invalidate(0, updatePop = $$props.updatePop);
    		if ('id' in $$props) $$invalidate(5, id = $$props.id);
    	};

    	$$self.$capture_state = () => ({
    		createEventDispatcher,
    		hostname,
    		dispatch,
    		updatePop,
    		id,
    		badUpdate,
    		indexBadUpdate,
    		submitForm,
    		closePopUp
    	});

    	$$self.$inject_state = $$props => {
    		if ('updatePop' in $$props) $$invalidate(0, updatePop = $$props.updatePop);
    		if ('id' in $$props) $$invalidate(5, id = $$props.id);
    		if ('badUpdate' in $$props) $$invalidate(1, badUpdate = $$props.badUpdate);
    		if ('indexBadUpdate' in $$props) $$invalidate(2, indexBadUpdate = $$props.indexBadUpdate);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [
    		updatePop,
    		badUpdate,
    		indexBadUpdate,
    		submitForm,
    		closePopUp,
    		id,
    		click_handler,
    		keypress_handler,
    		click_handler_1,
    		click_handler_2,
    		keypress_handler_1,
    		click_handler_3
    	];
    }

    class Update extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$a, create_fragment$a, safe_not_equal, { updatePop: 0, id: 5 });

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Update",
    			options,
    			id: create_fragment$a.name
    		});
    	}

    	get updatePop() {
    		throw new Error("<Update>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set updatePop(value) {
    		throw new Error("<Update>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	get id() {
    		throw new Error("<Update>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set id(value) {
    		throw new Error("<Update>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/component/dashboard/Delete.svelte generated by Svelte v3.59.1 */

    const file$9 = "src/component/dashboard/Delete.svelte";

    // (5:0) {#if deletePop}
    function create_if_block$6(ctx) {
    	let div1;
    	let div0;
    	let h1;
    	let t1;
    	let p0;
    	let t3;
    	let p1;
    	let t5;
    	let p2;
    	let t7;
    	let p3;
    	let t9;
    	let p4;
    	let t11;
    	let p5;
    	let mounted;
    	let dispose;

    	const block = {
    		c: function create() {
    			div1 = element("div");
    			div0 = element("div");
    			h1 = element("h1");
    			h1.textContent = "Plz stay...";
    			t1 = space();
    			p0 = element("p");
    			p0.textContent = "we can work this out";
    			t3 = space();
    			p1 = element("p");
    			p1.textContent = "i know its me, not you";
    			t5 = space();
    			p2 = element("p");
    			p2.textContent = "you know it's kinda hard for me right now";
    			t7 = space();
    			p3 = element("p");
    			p3.textContent = "but i can change";
    			t9 = space();
    			p4 = element("p");
    			p4.textContent = "i ll be better i promise";
    			t11 = space();
    			p5 = element("p");
    			p5.textContent = "i love u";
    			attr_dev(h1, "class", "svelte-13j1fsy");
    			add_location(h1, file$9, 7, 3, 134);
    			attr_dev(p0, "class", "svelte-13j1fsy");
    			add_location(p0, file$9, 8, 3, 158);
    			attr_dev(p1, "class", "svelte-13j1fsy");
    			add_location(p1, file$9, 9, 3, 189);
    			attr_dev(p2, "class", "svelte-13j1fsy");
    			add_location(p2, file$9, 10, 3, 222);
    			attr_dev(p3, "class", "svelte-13j1fsy");
    			add_location(p3, file$9, 11, 3, 274);
    			attr_dev(p4, "class", "svelte-13j1fsy");
    			add_location(p4, file$9, 12, 3, 301);
    			attr_dev(p5, "class", "svelte-13j1fsy");
    			add_location(p5, file$9, 13, 3, 336);
    			attr_dev(div0, "class", "modal svelte-13j1fsy");
    			add_location(div0, file$9, 6, 2, 111);
    			attr_dev(div1, "class", "backdrop svelte-13j1fsy");
    			add_location(div1, file$9, 5, 1, 60);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div1, anchor);
    			append_dev(div1, div0);
    			append_dev(div0, h1);
    			append_dev(div0, t1);
    			append_dev(div0, p0);
    			append_dev(div0, t3);
    			append_dev(div0, p1);
    			append_dev(div0, t5);
    			append_dev(div0, p2);
    			append_dev(div0, t7);
    			append_dev(div0, p3);
    			append_dev(div0, t9);
    			append_dev(div0, p4);
    			append_dev(div0, t11);
    			append_dev(div0, p5);

    			if (!mounted) {
    				dispose = [
    					listen_dev(div1, "click", self$1(/*click_handler*/ ctx[1]), false, false, false, false),
    					listen_dev(div1, "keypress", /*keypress_handler*/ ctx[2], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div1);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block$6.name,
    		type: "if",
    		source: "(5:0) {#if deletePop}",
    		ctx
    	});

    	return block;
    }

    function create_fragment$9(ctx) {
    	let if_block_anchor;
    	let if_block = /*deletePop*/ ctx[0] && create_if_block$6(ctx);

    	const block = {
    		c: function create() {
    			if (if_block) if_block.c();
    			if_block_anchor = empty$1();
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			if (if_block) if_block.m(target, anchor);
    			insert_dev(target, if_block_anchor, anchor);
    		},
    		p: function update(ctx, [dirty]) {
    			if (/*deletePop*/ ctx[0]) {
    				if (if_block) ; else {
    					if_block = create_if_block$6(ctx);
    					if_block.c();
    					if_block.m(if_block_anchor.parentNode, if_block_anchor);
    				}
    			} else if (if_block) {
    				if_block.d(1);
    				if_block = null;
    			}
    		},
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (if_block) if_block.d(detaching);
    			if (detaching) detach_dev(if_block_anchor);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$9.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$9($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Delete', slots, []);
    	let { deletePop } = $$props;

    	$$self.$$.on_mount.push(function () {
    		if (deletePop === undefined && !('deletePop' in $$props || $$self.$$.bound[$$self.$$.props['deletePop']])) {
    			console.warn("<Delete> was created without expected prop 'deletePop'");
    		}
    	});

    	const writable_props = ['deletePop'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console.warn(`<Delete> was created with unknown prop '${key}'`);
    	});

    	function click_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	function keypress_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	$$self.$$set = $$props => {
    		if ('deletePop' in $$props) $$invalidate(0, deletePop = $$props.deletePop);
    	};

    	$$self.$capture_state = () => ({ deletePop });

    	$$self.$inject_state = $$props => {
    		if ('deletePop' in $$props) $$invalidate(0, deletePop = $$props.deletePop);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [deletePop, click_handler, keypress_handler];
    }

    class Delete extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$9, create_fragment$9, safe_not_equal, { deletePop: 0 });

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Delete",
    			options,
    			id: create_fragment$9.name
    		});
    	}

    	get deletePop() {
    		throw new Error("<Delete>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set deletePop(value) {
    		throw new Error("<Delete>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    function bind(fn, thisArg) {
      return function wrap() {
        return fn.apply(thisArg, arguments);
      };
    }

    // utils is a library of generic helper functions non-specific to axios

    const {toString} = Object.prototype;
    const {getPrototypeOf} = Object;

    const kindOf = (cache => thing => {
        const str = toString.call(thing);
        return cache[str] || (cache[str] = str.slice(8, -1).toLowerCase());
    })(Object.create(null));

    const kindOfTest = (type) => {
      type = type.toLowerCase();
      return (thing) => kindOf(thing) === type
    };

    const typeOfTest = type => thing => typeof thing === type;

    /**
     * Determine if a value is an Array
     *
     * @param {Object} val The value to test
     *
     * @returns {boolean} True if value is an Array, otherwise false
     */
    const {isArray} = Array;

    /**
     * Determine if a value is undefined
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if the value is undefined, otherwise false
     */
    const isUndefined = typeOfTest('undefined');

    /**
     * Determine if a value is a Buffer
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is a Buffer, otherwise false
     */
    function isBuffer(val) {
      return val !== null && !isUndefined(val) && val.constructor !== null && !isUndefined(val.constructor)
        && isFunction(val.constructor.isBuffer) && val.constructor.isBuffer(val);
    }

    /**
     * Determine if a value is an ArrayBuffer
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is an ArrayBuffer, otherwise false
     */
    const isArrayBuffer = kindOfTest('ArrayBuffer');


    /**
     * Determine if a value is a view on an ArrayBuffer
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is a view on an ArrayBuffer, otherwise false
     */
    function isArrayBufferView(val) {
      let result;
      if ((typeof ArrayBuffer !== 'undefined') && (ArrayBuffer.isView)) {
        result = ArrayBuffer.isView(val);
      } else {
        result = (val) && (val.buffer) && (isArrayBuffer(val.buffer));
      }
      return result;
    }

    /**
     * Determine if a value is a String
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is a String, otherwise false
     */
    const isString = typeOfTest('string');

    /**
     * Determine if a value is a Function
     *
     * @param {*} val The value to test
     * @returns {boolean} True if value is a Function, otherwise false
     */
    const isFunction = typeOfTest('function');

    /**
     * Determine if a value is a Number
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is a Number, otherwise false
     */
    const isNumber = typeOfTest('number');

    /**
     * Determine if a value is an Object
     *
     * @param {*} thing The value to test
     *
     * @returns {boolean} True if value is an Object, otherwise false
     */
    const isObject = (thing) => thing !== null && typeof thing === 'object';

    /**
     * Determine if a value is a Boolean
     *
     * @param {*} thing The value to test
     * @returns {boolean} True if value is a Boolean, otherwise false
     */
    const isBoolean = thing => thing === true || thing === false;

    /**
     * Determine if a value is a plain Object
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is a plain Object, otherwise false
     */
    const isPlainObject = (val) => {
      if (kindOf(val) !== 'object') {
        return false;
      }

      const prototype = getPrototypeOf(val);
      return (prototype === null || prototype === Object.prototype || Object.getPrototypeOf(prototype) === null) && !(Symbol.toStringTag in val) && !(Symbol.iterator in val);
    };

    /**
     * Determine if a value is a Date
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is a Date, otherwise false
     */
    const isDate = kindOfTest('Date');

    /**
     * Determine if a value is a File
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is a File, otherwise false
     */
    const isFile = kindOfTest('File');

    /**
     * Determine if a value is a Blob
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is a Blob, otherwise false
     */
    const isBlob = kindOfTest('Blob');

    /**
     * Determine if a value is a FileList
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is a File, otherwise false
     */
    const isFileList = kindOfTest('FileList');

    /**
     * Determine if a value is a Stream
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is a Stream, otherwise false
     */
    const isStream = (val) => isObject(val) && isFunction(val.pipe);

    /**
     * Determine if a value is a FormData
     *
     * @param {*} thing The value to test
     *
     * @returns {boolean} True if value is an FormData, otherwise false
     */
    const isFormData = (thing) => {
      let kind;
      return thing && (
        (typeof FormData === 'function' && thing instanceof FormData) || (
          isFunction(thing.append) && (
            (kind = kindOf(thing)) === 'formdata' ||
            // detect form-data instance
            (kind === 'object' && isFunction(thing.toString) && thing.toString() === '[object FormData]')
          )
        )
      )
    };

    /**
     * Determine if a value is a URLSearchParams object
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is a URLSearchParams object, otherwise false
     */
    const isURLSearchParams = kindOfTest('URLSearchParams');

    /**
     * Trim excess whitespace off the beginning and end of a string
     *
     * @param {String} str The String to trim
     *
     * @returns {String} The String freed of excess whitespace
     */
    const trim = (str) => str.trim ?
      str.trim() : str.replace(/^[\s\uFEFF\xA0]+|[\s\uFEFF\xA0]+$/g, '');

    /**
     * Iterate over an Array or an Object invoking a function for each item.
     *
     * If `obj` is an Array callback will be called passing
     * the value, index, and complete array for each item.
     *
     * If 'obj' is an Object callback will be called passing
     * the value, key, and complete object for each property.
     *
     * @param {Object|Array} obj The object to iterate
     * @param {Function} fn The callback to invoke for each item
     *
     * @param {Boolean} [allOwnKeys = false]
     * @returns {any}
     */
    function forEach(obj, fn, {allOwnKeys = false} = {}) {
      // Don't bother if no value provided
      if (obj === null || typeof obj === 'undefined') {
        return;
      }

      let i;
      let l;

      // Force an array if not already something iterable
      if (typeof obj !== 'object') {
        /*eslint no-param-reassign:0*/
        obj = [obj];
      }

      if (isArray(obj)) {
        // Iterate over array values
        for (i = 0, l = obj.length; i < l; i++) {
          fn.call(null, obj[i], i, obj);
        }
      } else {
        // Iterate over object keys
        const keys = allOwnKeys ? Object.getOwnPropertyNames(obj) : Object.keys(obj);
        const len = keys.length;
        let key;

        for (i = 0; i < len; i++) {
          key = keys[i];
          fn.call(null, obj[key], key, obj);
        }
      }
    }

    function findKey(obj, key) {
      key = key.toLowerCase();
      const keys = Object.keys(obj);
      let i = keys.length;
      let _key;
      while (i-- > 0) {
        _key = keys[i];
        if (key === _key.toLowerCase()) {
          return _key;
        }
      }
      return null;
    }

    const _global = (() => {
      /*eslint no-undef:0*/
      if (typeof globalThis !== "undefined") return globalThis;
      return typeof self !== "undefined" ? self : (typeof window !== 'undefined' ? window : global)
    })();

    const isContextDefined = (context) => !isUndefined(context) && context !== _global;

    /**
     * Accepts varargs expecting each argument to be an object, then
     * immutably merges the properties of each object and returns result.
     *
     * When multiple objects contain the same key the later object in
     * the arguments list will take precedence.
     *
     * Example:
     *
     * ```js
     * var result = merge({foo: 123}, {foo: 456});
     * console.log(result.foo); // outputs 456
     * ```
     *
     * @param {Object} obj1 Object to merge
     *
     * @returns {Object} Result of all merge properties
     */
    function merge(/* obj1, obj2, obj3, ... */) {
      const {caseless} = isContextDefined(this) && this || {};
      const result = {};
      const assignValue = (val, key) => {
        const targetKey = caseless && findKey(result, key) || key;
        if (isPlainObject(result[targetKey]) && isPlainObject(val)) {
          result[targetKey] = merge(result[targetKey], val);
        } else if (isPlainObject(val)) {
          result[targetKey] = merge({}, val);
        } else if (isArray(val)) {
          result[targetKey] = val.slice();
        } else {
          result[targetKey] = val;
        }
      };

      for (let i = 0, l = arguments.length; i < l; i++) {
        arguments[i] && forEach(arguments[i], assignValue);
      }
      return result;
    }

    /**
     * Extends object a by mutably adding to it the properties of object b.
     *
     * @param {Object} a The object to be extended
     * @param {Object} b The object to copy properties from
     * @param {Object} thisArg The object to bind function to
     *
     * @param {Boolean} [allOwnKeys]
     * @returns {Object} The resulting value of object a
     */
    const extend = (a, b, thisArg, {allOwnKeys}= {}) => {
      forEach(b, (val, key) => {
        if (thisArg && isFunction(val)) {
          a[key] = bind(val, thisArg);
        } else {
          a[key] = val;
        }
      }, {allOwnKeys});
      return a;
    };

    /**
     * Remove byte order marker. This catches EF BB BF (the UTF-8 BOM)
     *
     * @param {string} content with BOM
     *
     * @returns {string} content value without BOM
     */
    const stripBOM = (content) => {
      if (content.charCodeAt(0) === 0xFEFF) {
        content = content.slice(1);
      }
      return content;
    };

    /**
     * Inherit the prototype methods from one constructor into another
     * @param {function} constructor
     * @param {function} superConstructor
     * @param {object} [props]
     * @param {object} [descriptors]
     *
     * @returns {void}
     */
    const inherits = (constructor, superConstructor, props, descriptors) => {
      constructor.prototype = Object.create(superConstructor.prototype, descriptors);
      constructor.prototype.constructor = constructor;
      Object.defineProperty(constructor, 'super', {
        value: superConstructor.prototype
      });
      props && Object.assign(constructor.prototype, props);
    };

    /**
     * Resolve object with deep prototype chain to a flat object
     * @param {Object} sourceObj source object
     * @param {Object} [destObj]
     * @param {Function|Boolean} [filter]
     * @param {Function} [propFilter]
     *
     * @returns {Object}
     */
    const toFlatObject = (sourceObj, destObj, filter, propFilter) => {
      let props;
      let i;
      let prop;
      const merged = {};

      destObj = destObj || {};
      // eslint-disable-next-line no-eq-null,eqeqeq
      if (sourceObj == null) return destObj;

      do {
        props = Object.getOwnPropertyNames(sourceObj);
        i = props.length;
        while (i-- > 0) {
          prop = props[i];
          if ((!propFilter || propFilter(prop, sourceObj, destObj)) && !merged[prop]) {
            destObj[prop] = sourceObj[prop];
            merged[prop] = true;
          }
        }
        sourceObj = filter !== false && getPrototypeOf(sourceObj);
      } while (sourceObj && (!filter || filter(sourceObj, destObj)) && sourceObj !== Object.prototype);

      return destObj;
    };

    /**
     * Determines whether a string ends with the characters of a specified string
     *
     * @param {String} str
     * @param {String} searchString
     * @param {Number} [position= 0]
     *
     * @returns {boolean}
     */
    const endsWith = (str, searchString, position) => {
      str = String(str);
      if (position === undefined || position > str.length) {
        position = str.length;
      }
      position -= searchString.length;
      const lastIndex = str.indexOf(searchString, position);
      return lastIndex !== -1 && lastIndex === position;
    };


    /**
     * Returns new array from array like object or null if failed
     *
     * @param {*} [thing]
     *
     * @returns {?Array}
     */
    const toArray = (thing) => {
      if (!thing) return null;
      if (isArray(thing)) return thing;
      let i = thing.length;
      if (!isNumber(i)) return null;
      const arr = new Array(i);
      while (i-- > 0) {
        arr[i] = thing[i];
      }
      return arr;
    };

    /**
     * Checking if the Uint8Array exists and if it does, it returns a function that checks if the
     * thing passed in is an instance of Uint8Array
     *
     * @param {TypedArray}
     *
     * @returns {Array}
     */
    // eslint-disable-next-line func-names
    const isTypedArray = (TypedArray => {
      // eslint-disable-next-line func-names
      return thing => {
        return TypedArray && thing instanceof TypedArray;
      };
    })(typeof Uint8Array !== 'undefined' && getPrototypeOf(Uint8Array));

    /**
     * For each entry in the object, call the function with the key and value.
     *
     * @param {Object<any, any>} obj - The object to iterate over.
     * @param {Function} fn - The function to call for each entry.
     *
     * @returns {void}
     */
    const forEachEntry = (obj, fn) => {
      const generator = obj && obj[Symbol.iterator];

      const iterator = generator.call(obj);

      let result;

      while ((result = iterator.next()) && !result.done) {
        const pair = result.value;
        fn.call(obj, pair[0], pair[1]);
      }
    };

    /**
     * It takes a regular expression and a string, and returns an array of all the matches
     *
     * @param {string} regExp - The regular expression to match against.
     * @param {string} str - The string to search.
     *
     * @returns {Array<boolean>}
     */
    const matchAll = (regExp, str) => {
      let matches;
      const arr = [];

      while ((matches = regExp.exec(str)) !== null) {
        arr.push(matches);
      }

      return arr;
    };

    /* Checking if the kindOfTest function returns true when passed an HTMLFormElement. */
    const isHTMLForm = kindOfTest('HTMLFormElement');

    const toCamelCase = str => {
      return str.toLowerCase().replace(/[-_\s]([a-z\d])(\w*)/g,
        function replacer(m, p1, p2) {
          return p1.toUpperCase() + p2;
        }
      );
    };

    /* Creating a function that will check if an object has a property. */
    const hasOwnProperty = (({hasOwnProperty}) => (obj, prop) => hasOwnProperty.call(obj, prop))(Object.prototype);

    /**
     * Determine if a value is a RegExp object
     *
     * @param {*} val The value to test
     *
     * @returns {boolean} True if value is a RegExp object, otherwise false
     */
    const isRegExp = kindOfTest('RegExp');

    const reduceDescriptors = (obj, reducer) => {
      const descriptors = Object.getOwnPropertyDescriptors(obj);
      const reducedDescriptors = {};

      forEach(descriptors, (descriptor, name) => {
        if (reducer(descriptor, name, obj) !== false) {
          reducedDescriptors[name] = descriptor;
        }
      });

      Object.defineProperties(obj, reducedDescriptors);
    };

    /**
     * Makes all methods read-only
     * @param {Object} obj
     */

    const freezeMethods = (obj) => {
      reduceDescriptors(obj, (descriptor, name) => {
        // skip restricted props in strict mode
        if (isFunction(obj) && ['arguments', 'caller', 'callee'].indexOf(name) !== -1) {
          return false;
        }

        const value = obj[name];

        if (!isFunction(value)) return;

        descriptor.enumerable = false;

        if ('writable' in descriptor) {
          descriptor.writable = false;
          return;
        }

        if (!descriptor.set) {
          descriptor.set = () => {
            throw Error('Can not rewrite read-only method \'' + name + '\'');
          };
        }
      });
    };

    const toObjectSet = (arrayOrString, delimiter) => {
      const obj = {};

      const define = (arr) => {
        arr.forEach(value => {
          obj[value] = true;
        });
      };

      isArray(arrayOrString) ? define(arrayOrString) : define(String(arrayOrString).split(delimiter));

      return obj;
    };

    const noop = () => {};

    const toFiniteNumber = (value, defaultValue) => {
      value = +value;
      return Number.isFinite(value) ? value : defaultValue;
    };

    const ALPHA = 'abcdefghijklmnopqrstuvwxyz';

    const DIGIT = '0123456789';

    const ALPHABET = {
      DIGIT,
      ALPHA,
      ALPHA_DIGIT: ALPHA + ALPHA.toUpperCase() + DIGIT
    };

    const generateString = (size = 16, alphabet = ALPHABET.ALPHA_DIGIT) => {
      let str = '';
      const {length} = alphabet;
      while (size--) {
        str += alphabet[Math.random() * length|0];
      }

      return str;
    };

    /**
     * If the thing is a FormData object, return true, otherwise return false.
     *
     * @param {unknown} thing - The thing to check.
     *
     * @returns {boolean}
     */
    function isSpecCompliantForm(thing) {
      return !!(thing && isFunction(thing.append) && thing[Symbol.toStringTag] === 'FormData' && thing[Symbol.iterator]);
    }

    const toJSONObject = (obj) => {
      const stack = new Array(10);

      const visit = (source, i) => {

        if (isObject(source)) {
          if (stack.indexOf(source) >= 0) {
            return;
          }

          if(!('toJSON' in source)) {
            stack[i] = source;
            const target = isArray(source) ? [] : {};

            forEach(source, (value, key) => {
              const reducedValue = visit(value, i + 1);
              !isUndefined(reducedValue) && (target[key] = reducedValue);
            });

            stack[i] = undefined;

            return target;
          }
        }

        return source;
      };

      return visit(obj, 0);
    };

    const isAsyncFn = kindOfTest('AsyncFunction');

    const isThenable = (thing) =>
      thing && (isObject(thing) || isFunction(thing)) && isFunction(thing.then) && isFunction(thing.catch);

    var utils = {
      isArray,
      isArrayBuffer,
      isBuffer,
      isFormData,
      isArrayBufferView,
      isString,
      isNumber,
      isBoolean,
      isObject,
      isPlainObject,
      isUndefined,
      isDate,
      isFile,
      isBlob,
      isRegExp,
      isFunction,
      isStream,
      isURLSearchParams,
      isTypedArray,
      isFileList,
      forEach,
      merge,
      extend,
      trim,
      stripBOM,
      inherits,
      toFlatObject,
      kindOf,
      kindOfTest,
      endsWith,
      toArray,
      forEachEntry,
      matchAll,
      isHTMLForm,
      hasOwnProperty,
      hasOwnProp: hasOwnProperty, // an alias to avoid ESLint no-prototype-builtins detection
      reduceDescriptors,
      freezeMethods,
      toObjectSet,
      toCamelCase,
      noop,
      toFiniteNumber,
      findKey,
      global: _global,
      isContextDefined,
      ALPHABET,
      generateString,
      isSpecCompliantForm,
      toJSONObject,
      isAsyncFn,
      isThenable
    };

    /**
     * Create an Error with the specified message, config, error code, request and response.
     *
     * @param {string} message The error message.
     * @param {string} [code] The error code (for example, 'ECONNABORTED').
     * @param {Object} [config] The config.
     * @param {Object} [request] The request.
     * @param {Object} [response] The response.
     *
     * @returns {Error} The created error.
     */
    function AxiosError(message, code, config, request, response) {
      Error.call(this);

      if (Error.captureStackTrace) {
        Error.captureStackTrace(this, this.constructor);
      } else {
        this.stack = (new Error()).stack;
      }

      this.message = message;
      this.name = 'AxiosError';
      code && (this.code = code);
      config && (this.config = config);
      request && (this.request = request);
      response && (this.response = response);
    }

    utils.inherits(AxiosError, Error, {
      toJSON: function toJSON() {
        return {
          // Standard
          message: this.message,
          name: this.name,
          // Microsoft
          description: this.description,
          number: this.number,
          // Mozilla
          fileName: this.fileName,
          lineNumber: this.lineNumber,
          columnNumber: this.columnNumber,
          stack: this.stack,
          // Axios
          config: utils.toJSONObject(this.config),
          code: this.code,
          status: this.response && this.response.status ? this.response.status : null
        };
      }
    });

    const prototype$1 = AxiosError.prototype;
    const descriptors = {};

    [
      'ERR_BAD_OPTION_VALUE',
      'ERR_BAD_OPTION',
      'ECONNABORTED',
      'ETIMEDOUT',
      'ERR_NETWORK',
      'ERR_FR_TOO_MANY_REDIRECTS',
      'ERR_DEPRECATED',
      'ERR_BAD_RESPONSE',
      'ERR_BAD_REQUEST',
      'ERR_CANCELED',
      'ERR_NOT_SUPPORT',
      'ERR_INVALID_URL'
    // eslint-disable-next-line func-names
    ].forEach(code => {
      descriptors[code] = {value: code};
    });

    Object.defineProperties(AxiosError, descriptors);
    Object.defineProperty(prototype$1, 'isAxiosError', {value: true});

    // eslint-disable-next-line func-names
    AxiosError.from = (error, code, config, request, response, customProps) => {
      const axiosError = Object.create(prototype$1);

      utils.toFlatObject(error, axiosError, function filter(obj) {
        return obj !== Error.prototype;
      }, prop => {
        return prop !== 'isAxiosError';
      });

      AxiosError.call(axiosError, error.message, code, config, request, response);

      axiosError.cause = error;

      axiosError.name = error.name;

      customProps && Object.assign(axiosError, customProps);

      return axiosError;
    };

    // eslint-disable-next-line strict
    var httpAdapter = null;

    /**
     * Determines if the given thing is a array or js object.
     *
     * @param {string} thing - The object or array to be visited.
     *
     * @returns {boolean}
     */
    function isVisitable(thing) {
      return utils.isPlainObject(thing) || utils.isArray(thing);
    }

    /**
     * It removes the brackets from the end of a string
     *
     * @param {string} key - The key of the parameter.
     *
     * @returns {string} the key without the brackets.
     */
    function removeBrackets(key) {
      return utils.endsWith(key, '[]') ? key.slice(0, -2) : key;
    }

    /**
     * It takes a path, a key, and a boolean, and returns a string
     *
     * @param {string} path - The path to the current key.
     * @param {string} key - The key of the current object being iterated over.
     * @param {string} dots - If true, the key will be rendered with dots instead of brackets.
     *
     * @returns {string} The path to the current key.
     */
    function renderKey(path, key, dots) {
      if (!path) return key;
      return path.concat(key).map(function each(token, i) {
        // eslint-disable-next-line no-param-reassign
        token = removeBrackets(token);
        return !dots && i ? '[' + token + ']' : token;
      }).join(dots ? '.' : '');
    }

    /**
     * If the array is an array and none of its elements are visitable, then it's a flat array.
     *
     * @param {Array<any>} arr - The array to check
     *
     * @returns {boolean}
     */
    function isFlatArray(arr) {
      return utils.isArray(arr) && !arr.some(isVisitable);
    }

    const predicates = utils.toFlatObject(utils, {}, null, function filter(prop) {
      return /^is[A-Z]/.test(prop);
    });

    /**
     * Convert a data object to FormData
     *
     * @param {Object} obj
     * @param {?Object} [formData]
     * @param {?Object} [options]
     * @param {Function} [options.visitor]
     * @param {Boolean} [options.metaTokens = true]
     * @param {Boolean} [options.dots = false]
     * @param {?Boolean} [options.indexes = false]
     *
     * @returns {Object}
     **/

    /**
     * It converts an object into a FormData object
     *
     * @param {Object<any, any>} obj - The object to convert to form data.
     * @param {string} formData - The FormData object to append to.
     * @param {Object<string, any>} options
     *
     * @returns
     */
    function toFormData(obj, formData, options) {
      if (!utils.isObject(obj)) {
        throw new TypeError('target must be an object');
      }

      // eslint-disable-next-line no-param-reassign
      formData = formData || new (FormData)();

      // eslint-disable-next-line no-param-reassign
      options = utils.toFlatObject(options, {
        metaTokens: true,
        dots: false,
        indexes: false
      }, false, function defined(option, source) {
        // eslint-disable-next-line no-eq-null,eqeqeq
        return !utils.isUndefined(source[option]);
      });

      const metaTokens = options.metaTokens;
      // eslint-disable-next-line no-use-before-define
      const visitor = options.visitor || defaultVisitor;
      const dots = options.dots;
      const indexes = options.indexes;
      const _Blob = options.Blob || typeof Blob !== 'undefined' && Blob;
      const useBlob = _Blob && utils.isSpecCompliantForm(formData);

      if (!utils.isFunction(visitor)) {
        throw new TypeError('visitor must be a function');
      }

      function convertValue(value) {
        if (value === null) return '';

        if (utils.isDate(value)) {
          return value.toISOString();
        }

        if (!useBlob && utils.isBlob(value)) {
          throw new AxiosError('Blob is not supported. Use a Buffer instead.');
        }

        if (utils.isArrayBuffer(value) || utils.isTypedArray(value)) {
          return useBlob && typeof Blob === 'function' ? new Blob([value]) : Buffer.from(value);
        }

        return value;
      }

      /**
       * Default visitor.
       *
       * @param {*} value
       * @param {String|Number} key
       * @param {Array<String|Number>} path
       * @this {FormData}
       *
       * @returns {boolean} return true to visit the each prop of the value recursively
       */
      function defaultVisitor(value, key, path) {
        let arr = value;

        if (value && !path && typeof value === 'object') {
          if (utils.endsWith(key, '{}')) {
            // eslint-disable-next-line no-param-reassign
            key = metaTokens ? key : key.slice(0, -2);
            // eslint-disable-next-line no-param-reassign
            value = JSON.stringify(value);
          } else if (
            (utils.isArray(value) && isFlatArray(value)) ||
            ((utils.isFileList(value) || utils.endsWith(key, '[]')) && (arr = utils.toArray(value))
            )) {
            // eslint-disable-next-line no-param-reassign
            key = removeBrackets(key);

            arr.forEach(function each(el, index) {
              !(utils.isUndefined(el) || el === null) && formData.append(
                // eslint-disable-next-line no-nested-ternary
                indexes === true ? renderKey([key], index, dots) : (indexes === null ? key : key + '[]'),
                convertValue(el)
              );
            });
            return false;
          }
        }

        if (isVisitable(value)) {
          return true;
        }

        formData.append(renderKey(path, key, dots), convertValue(value));

        return false;
      }

      const stack = [];

      const exposedHelpers = Object.assign(predicates, {
        defaultVisitor,
        convertValue,
        isVisitable
      });

      function build(value, path) {
        if (utils.isUndefined(value)) return;

        if (stack.indexOf(value) !== -1) {
          throw Error('Circular reference detected in ' + path.join('.'));
        }

        stack.push(value);

        utils.forEach(value, function each(el, key) {
          const result = !(utils.isUndefined(el) || el === null) && visitor.call(
            formData, el, utils.isString(key) ? key.trim() : key, path, exposedHelpers
          );

          if (result === true) {
            build(el, path ? path.concat(key) : [key]);
          }
        });

        stack.pop();
      }

      if (!utils.isObject(obj)) {
        throw new TypeError('data must be an object');
      }

      build(obj);

      return formData;
    }

    /**
     * It encodes a string by replacing all characters that are not in the unreserved set with
     * their percent-encoded equivalents
     *
     * @param {string} str - The string to encode.
     *
     * @returns {string} The encoded string.
     */
    function encode$1(str) {
      const charMap = {
        '!': '%21',
        "'": '%27',
        '(': '%28',
        ')': '%29',
        '~': '%7E',
        '%20': '+',
        '%00': '\x00'
      };
      return encodeURIComponent(str).replace(/[!'()~]|%20|%00/g, function replacer(match) {
        return charMap[match];
      });
    }

    /**
     * It takes a params object and converts it to a FormData object
     *
     * @param {Object<string, any>} params - The parameters to be converted to a FormData object.
     * @param {Object<string, any>} options - The options object passed to the Axios constructor.
     *
     * @returns {void}
     */
    function AxiosURLSearchParams(params, options) {
      this._pairs = [];

      params && toFormData(params, this, options);
    }

    const prototype = AxiosURLSearchParams.prototype;

    prototype.append = function append(name, value) {
      this._pairs.push([name, value]);
    };

    prototype.toString = function toString(encoder) {
      const _encode = encoder ? function(value) {
        return encoder.call(this, value, encode$1);
      } : encode$1;

      return this._pairs.map(function each(pair) {
        return _encode(pair[0]) + '=' + _encode(pair[1]);
      }, '').join('&');
    };

    /**
     * It replaces all instances of the characters `:`, `$`, `,`, `+`, `[`, and `]` with their
     * URI encoded counterparts
     *
     * @param {string} val The value to be encoded.
     *
     * @returns {string} The encoded value.
     */
    function encode(val) {
      return encodeURIComponent(val).
        replace(/%3A/gi, ':').
        replace(/%24/g, '$').
        replace(/%2C/gi, ',').
        replace(/%20/g, '+').
        replace(/%5B/gi, '[').
        replace(/%5D/gi, ']');
    }

    /**
     * Build a URL by appending params to the end
     *
     * @param {string} url The base of the url (e.g., http://www.google.com)
     * @param {object} [params] The params to be appended
     * @param {?object} options
     *
     * @returns {string} The formatted url
     */
    function buildURL(url, params, options) {
      /*eslint no-param-reassign:0*/
      if (!params) {
        return url;
      }
      
      const _encode = options && options.encode || encode;

      const serializeFn = options && options.serialize;

      let serializedParams;

      if (serializeFn) {
        serializedParams = serializeFn(params, options);
      } else {
        serializedParams = utils.isURLSearchParams(params) ?
          params.toString() :
          new AxiosURLSearchParams(params, options).toString(_encode);
      }

      if (serializedParams) {
        const hashmarkIndex = url.indexOf("#");

        if (hashmarkIndex !== -1) {
          url = url.slice(0, hashmarkIndex);
        }
        url += (url.indexOf('?') === -1 ? '?' : '&') + serializedParams;
      }

      return url;
    }

    class InterceptorManager {
      constructor() {
        this.handlers = [];
      }

      /**
       * Add a new interceptor to the stack
       *
       * @param {Function} fulfilled The function to handle `then` for a `Promise`
       * @param {Function} rejected The function to handle `reject` for a `Promise`
       *
       * @return {Number} An ID used to remove interceptor later
       */
      use(fulfilled, rejected, options) {
        this.handlers.push({
          fulfilled,
          rejected,
          synchronous: options ? options.synchronous : false,
          runWhen: options ? options.runWhen : null
        });
        return this.handlers.length - 1;
      }

      /**
       * Remove an interceptor from the stack
       *
       * @param {Number} id The ID that was returned by `use`
       *
       * @returns {Boolean} `true` if the interceptor was removed, `false` otherwise
       */
      eject(id) {
        if (this.handlers[id]) {
          this.handlers[id] = null;
        }
      }

      /**
       * Clear all interceptors from the stack
       *
       * @returns {void}
       */
      clear() {
        if (this.handlers) {
          this.handlers = [];
        }
      }

      /**
       * Iterate over all the registered interceptors
       *
       * This method is particularly useful for skipping over any
       * interceptors that may have become `null` calling `eject`.
       *
       * @param {Function} fn The function to call for each interceptor
       *
       * @returns {void}
       */
      forEach(fn) {
        utils.forEach(this.handlers, function forEachHandler(h) {
          if (h !== null) {
            fn(h);
          }
        });
      }
    }

    var InterceptorManager$1 = InterceptorManager;

    var transitionalDefaults = {
      silentJSONParsing: true,
      forcedJSONParsing: true,
      clarifyTimeoutError: false
    };

    var URLSearchParams$1 = typeof URLSearchParams !== 'undefined' ? URLSearchParams : AxiosURLSearchParams;

    var FormData$1 = typeof FormData !== 'undefined' ? FormData : null;

    var Blob$1 = typeof Blob !== 'undefined' ? Blob : null;

    /**
     * Determine if we're running in a standard browser environment
     *
     * This allows axios to run in a web worker, and react-native.
     * Both environments support XMLHttpRequest, but not fully standard globals.
     *
     * web workers:
     *  typeof window -> undefined
     *  typeof document -> undefined
     *
     * react-native:
     *  navigator.product -> 'ReactNative'
     * nativescript
     *  navigator.product -> 'NativeScript' or 'NS'
     *
     * @returns {boolean}
     */
    const isStandardBrowserEnv = (() => {
      let product;
      if (typeof navigator !== 'undefined' && (
        (product = navigator.product) === 'ReactNative' ||
        product === 'NativeScript' ||
        product === 'NS')
      ) {
        return false;
      }

      return typeof window !== 'undefined' && typeof document !== 'undefined';
    })();

    /**
     * Determine if we're running in a standard browser webWorker environment
     *
     * Although the `isStandardBrowserEnv` method indicates that
     * `allows axios to run in a web worker`, the WebWorker will still be
     * filtered out due to its judgment standard
     * `typeof window !== 'undefined' && typeof document !== 'undefined'`.
     * This leads to a problem when axios post `FormData` in webWorker
     */
     const isStandardBrowserWebWorkerEnv = (() => {
      return (
        typeof WorkerGlobalScope !== 'undefined' &&
        // eslint-disable-next-line no-undef
        self instanceof WorkerGlobalScope &&
        typeof self.importScripts === 'function'
      );
    })();


    var platform = {
      isBrowser: true,
      classes: {
        URLSearchParams: URLSearchParams$1,
        FormData: FormData$1,
        Blob: Blob$1
      },
      isStandardBrowserEnv,
      isStandardBrowserWebWorkerEnv,
      protocols: ['http', 'https', 'file', 'blob', 'url', 'data']
    };

    function toURLEncodedForm(data, options) {
      return toFormData(data, new platform.classes.URLSearchParams(), Object.assign({
        visitor: function(value, key, path, helpers) {
          if (platform.isNode && utils.isBuffer(value)) {
            this.append(key, value.toString('base64'));
            return false;
          }

          return helpers.defaultVisitor.apply(this, arguments);
        }
      }, options));
    }

    /**
     * It takes a string like `foo[x][y][z]` and returns an array like `['foo', 'x', 'y', 'z']
     *
     * @param {string} name - The name of the property to get.
     *
     * @returns An array of strings.
     */
    function parsePropPath(name) {
      // foo[x][y][z]
      // foo.x.y.z
      // foo-x-y-z
      // foo x y z
      return utils.matchAll(/\w+|\[(\w*)]/g, name).map(match => {
        return match[0] === '[]' ? '' : match[1] || match[0];
      });
    }

    /**
     * Convert an array to an object.
     *
     * @param {Array<any>} arr - The array to convert to an object.
     *
     * @returns An object with the same keys and values as the array.
     */
    function arrayToObject(arr) {
      const obj = {};
      const keys = Object.keys(arr);
      let i;
      const len = keys.length;
      let key;
      for (i = 0; i < len; i++) {
        key = keys[i];
        obj[key] = arr[key];
      }
      return obj;
    }

    /**
     * It takes a FormData object and returns a JavaScript object
     *
     * @param {string} formData The FormData object to convert to JSON.
     *
     * @returns {Object<string, any> | null} The converted object.
     */
    function formDataToJSON(formData) {
      function buildPath(path, value, target, index) {
        let name = path[index++];
        const isNumericKey = Number.isFinite(+name);
        const isLast = index >= path.length;
        name = !name && utils.isArray(target) ? target.length : name;

        if (isLast) {
          if (utils.hasOwnProp(target, name)) {
            target[name] = [target[name], value];
          } else {
            target[name] = value;
          }

          return !isNumericKey;
        }

        if (!target[name] || !utils.isObject(target[name])) {
          target[name] = [];
        }

        const result = buildPath(path, value, target[name], index);

        if (result && utils.isArray(target[name])) {
          target[name] = arrayToObject(target[name]);
        }

        return !isNumericKey;
      }

      if (utils.isFormData(formData) && utils.isFunction(formData.entries)) {
        const obj = {};

        utils.forEachEntry(formData, (name, value) => {
          buildPath(parsePropPath(name), value, obj, 0);
        });

        return obj;
      }

      return null;
    }

    const DEFAULT_CONTENT_TYPE = {
      'Content-Type': undefined
    };

    /**
     * It takes a string, tries to parse it, and if it fails, it returns the stringified version
     * of the input
     *
     * @param {any} rawValue - The value to be stringified.
     * @param {Function} parser - A function that parses a string into a JavaScript object.
     * @param {Function} encoder - A function that takes a value and returns a string.
     *
     * @returns {string} A stringified version of the rawValue.
     */
    function stringifySafely(rawValue, parser, encoder) {
      if (utils.isString(rawValue)) {
        try {
          (parser || JSON.parse)(rawValue);
          return utils.trim(rawValue);
        } catch (e) {
          if (e.name !== 'SyntaxError') {
            throw e;
          }
        }
      }

      return (encoder || JSON.stringify)(rawValue);
    }

    const defaults = {

      transitional: transitionalDefaults,

      adapter: ['xhr', 'http'],

      transformRequest: [function transformRequest(data, headers) {
        const contentType = headers.getContentType() || '';
        const hasJSONContentType = contentType.indexOf('application/json') > -1;
        const isObjectPayload = utils.isObject(data);

        if (isObjectPayload && utils.isHTMLForm(data)) {
          data = new FormData(data);
        }

        const isFormData = utils.isFormData(data);

        if (isFormData) {
          if (!hasJSONContentType) {
            return data;
          }
          return hasJSONContentType ? JSON.stringify(formDataToJSON(data)) : data;
        }

        if (utils.isArrayBuffer(data) ||
          utils.isBuffer(data) ||
          utils.isStream(data) ||
          utils.isFile(data) ||
          utils.isBlob(data)
        ) {
          return data;
        }
        if (utils.isArrayBufferView(data)) {
          return data.buffer;
        }
        if (utils.isURLSearchParams(data)) {
          headers.setContentType('application/x-www-form-urlencoded;charset=utf-8', false);
          return data.toString();
        }

        let isFileList;

        if (isObjectPayload) {
          if (contentType.indexOf('application/x-www-form-urlencoded') > -1) {
            return toURLEncodedForm(data, this.formSerializer).toString();
          }

          if ((isFileList = utils.isFileList(data)) || contentType.indexOf('multipart/form-data') > -1) {
            const _FormData = this.env && this.env.FormData;

            return toFormData(
              isFileList ? {'files[]': data} : data,
              _FormData && new _FormData(),
              this.formSerializer
            );
          }
        }

        if (isObjectPayload || hasJSONContentType ) {
          headers.setContentType('application/json', false);
          return stringifySafely(data);
        }

        return data;
      }],

      transformResponse: [function transformResponse(data) {
        const transitional = this.transitional || defaults.transitional;
        const forcedJSONParsing = transitional && transitional.forcedJSONParsing;
        const JSONRequested = this.responseType === 'json';

        if (data && utils.isString(data) && ((forcedJSONParsing && !this.responseType) || JSONRequested)) {
          const silentJSONParsing = transitional && transitional.silentJSONParsing;
          const strictJSONParsing = !silentJSONParsing && JSONRequested;

          try {
            return JSON.parse(data);
          } catch (e) {
            if (strictJSONParsing) {
              if (e.name === 'SyntaxError') {
                throw AxiosError.from(e, AxiosError.ERR_BAD_RESPONSE, this, null, this.response);
              }
              throw e;
            }
          }
        }

        return data;
      }],

      /**
       * A timeout in milliseconds to abort a request. If set to 0 (default) a
       * timeout is not created.
       */
      timeout: 0,

      xsrfCookieName: 'XSRF-TOKEN',
      xsrfHeaderName: 'X-XSRF-TOKEN',

      maxContentLength: -1,
      maxBodyLength: -1,

      env: {
        FormData: platform.classes.FormData,
        Blob: platform.classes.Blob
      },

      validateStatus: function validateStatus(status) {
        return status >= 200 && status < 300;
      },

      headers: {
        common: {
          'Accept': 'application/json, text/plain, */*'
        }
      }
    };

    utils.forEach(['delete', 'get', 'head'], function forEachMethodNoData(method) {
      defaults.headers[method] = {};
    });

    utils.forEach(['post', 'put', 'patch'], function forEachMethodWithData(method) {
      defaults.headers[method] = utils.merge(DEFAULT_CONTENT_TYPE);
    });

    var defaults$1 = defaults;

    // RawAxiosHeaders whose duplicates are ignored by node
    // c.f. https://nodejs.org/api/http.html#http_message_headers
    const ignoreDuplicateOf = utils.toObjectSet([
      'age', 'authorization', 'content-length', 'content-type', 'etag',
      'expires', 'from', 'host', 'if-modified-since', 'if-unmodified-since',
      'last-modified', 'location', 'max-forwards', 'proxy-authorization',
      'referer', 'retry-after', 'user-agent'
    ]);

    /**
     * Parse headers into an object
     *
     * ```
     * Date: Wed, 27 Aug 2014 08:58:49 GMT
     * Content-Type: application/json
     * Connection: keep-alive
     * Transfer-Encoding: chunked
     * ```
     *
     * @param {String} rawHeaders Headers needing to be parsed
     *
     * @returns {Object} Headers parsed into an object
     */
    var parseHeaders = rawHeaders => {
      const parsed = {};
      let key;
      let val;
      let i;

      rawHeaders && rawHeaders.split('\n').forEach(function parser(line) {
        i = line.indexOf(':');
        key = line.substring(0, i).trim().toLowerCase();
        val = line.substring(i + 1).trim();

        if (!key || (parsed[key] && ignoreDuplicateOf[key])) {
          return;
        }

        if (key === 'set-cookie') {
          if (parsed[key]) {
            parsed[key].push(val);
          } else {
            parsed[key] = [val];
          }
        } else {
          parsed[key] = parsed[key] ? parsed[key] + ', ' + val : val;
        }
      });

      return parsed;
    };

    const $internals = Symbol('internals');

    function normalizeHeader(header) {
      return header && String(header).trim().toLowerCase();
    }

    function normalizeValue(value) {
      if (value === false || value == null) {
        return value;
      }

      return utils.isArray(value) ? value.map(normalizeValue) : String(value);
    }

    function parseTokens(str) {
      const tokens = Object.create(null);
      const tokensRE = /([^\s,;=]+)\s*(?:=\s*([^,;]+))?/g;
      let match;

      while ((match = tokensRE.exec(str))) {
        tokens[match[1]] = match[2];
      }

      return tokens;
    }

    const isValidHeaderName = (str) => /^[-_a-zA-Z0-9^`|~,!#$%&'*+.]+$/.test(str.trim());

    function matchHeaderValue(context, value, header, filter, isHeaderNameFilter) {
      if (utils.isFunction(filter)) {
        return filter.call(this, value, header);
      }

      if (isHeaderNameFilter) {
        value = header;
      }

      if (!utils.isString(value)) return;

      if (utils.isString(filter)) {
        return value.indexOf(filter) !== -1;
      }

      if (utils.isRegExp(filter)) {
        return filter.test(value);
      }
    }

    function formatHeader(header) {
      return header.trim()
        .toLowerCase().replace(/([a-z\d])(\w*)/g, (w, char, str) => {
          return char.toUpperCase() + str;
        });
    }

    function buildAccessors(obj, header) {
      const accessorName = utils.toCamelCase(' ' + header);

      ['get', 'set', 'has'].forEach(methodName => {
        Object.defineProperty(obj, methodName + accessorName, {
          value: function(arg1, arg2, arg3) {
            return this[methodName].call(this, header, arg1, arg2, arg3);
          },
          configurable: true
        });
      });
    }

    class AxiosHeaders {
      constructor(headers) {
        headers && this.set(headers);
      }

      set(header, valueOrRewrite, rewrite) {
        const self = this;

        function setHeader(_value, _header, _rewrite) {
          const lHeader = normalizeHeader(_header);

          if (!lHeader) {
            throw new Error('header name must be a non-empty string');
          }

          const key = utils.findKey(self, lHeader);

          if(!key || self[key] === undefined || _rewrite === true || (_rewrite === undefined && self[key] !== false)) {
            self[key || _header] = normalizeValue(_value);
          }
        }

        const setHeaders = (headers, _rewrite) =>
          utils.forEach(headers, (_value, _header) => setHeader(_value, _header, _rewrite));

        if (utils.isPlainObject(header) || header instanceof this.constructor) {
          setHeaders(header, valueOrRewrite);
        } else if(utils.isString(header) && (header = header.trim()) && !isValidHeaderName(header)) {
          setHeaders(parseHeaders(header), valueOrRewrite);
        } else {
          header != null && setHeader(valueOrRewrite, header, rewrite);
        }

        return this;
      }

      get(header, parser) {
        header = normalizeHeader(header);

        if (header) {
          const key = utils.findKey(this, header);

          if (key) {
            const value = this[key];

            if (!parser) {
              return value;
            }

            if (parser === true) {
              return parseTokens(value);
            }

            if (utils.isFunction(parser)) {
              return parser.call(this, value, key);
            }

            if (utils.isRegExp(parser)) {
              return parser.exec(value);
            }

            throw new TypeError('parser must be boolean|regexp|function');
          }
        }
      }

      has(header, matcher) {
        header = normalizeHeader(header);

        if (header) {
          const key = utils.findKey(this, header);

          return !!(key && this[key] !== undefined && (!matcher || matchHeaderValue(this, this[key], key, matcher)));
        }

        return false;
      }

      delete(header, matcher) {
        const self = this;
        let deleted = false;

        function deleteHeader(_header) {
          _header = normalizeHeader(_header);

          if (_header) {
            const key = utils.findKey(self, _header);

            if (key && (!matcher || matchHeaderValue(self, self[key], key, matcher))) {
              delete self[key];

              deleted = true;
            }
          }
        }

        if (utils.isArray(header)) {
          header.forEach(deleteHeader);
        } else {
          deleteHeader(header);
        }

        return deleted;
      }

      clear(matcher) {
        const keys = Object.keys(this);
        let i = keys.length;
        let deleted = false;

        while (i--) {
          const key = keys[i];
          if(!matcher || matchHeaderValue(this, this[key], key, matcher, true)) {
            delete this[key];
            deleted = true;
          }
        }

        return deleted;
      }

      normalize(format) {
        const self = this;
        const headers = {};

        utils.forEach(this, (value, header) => {
          const key = utils.findKey(headers, header);

          if (key) {
            self[key] = normalizeValue(value);
            delete self[header];
            return;
          }

          const normalized = format ? formatHeader(header) : String(header).trim();

          if (normalized !== header) {
            delete self[header];
          }

          self[normalized] = normalizeValue(value);

          headers[normalized] = true;
        });

        return this;
      }

      concat(...targets) {
        return this.constructor.concat(this, ...targets);
      }

      toJSON(asStrings) {
        const obj = Object.create(null);

        utils.forEach(this, (value, header) => {
          value != null && value !== false && (obj[header] = asStrings && utils.isArray(value) ? value.join(', ') : value);
        });

        return obj;
      }

      [Symbol.iterator]() {
        return Object.entries(this.toJSON())[Symbol.iterator]();
      }

      toString() {
        return Object.entries(this.toJSON()).map(([header, value]) => header + ': ' + value).join('\n');
      }

      get [Symbol.toStringTag]() {
        return 'AxiosHeaders';
      }

      static from(thing) {
        return thing instanceof this ? thing : new this(thing);
      }

      static concat(first, ...targets) {
        const computed = new this(first);

        targets.forEach((target) => computed.set(target));

        return computed;
      }

      static accessor(header) {
        const internals = this[$internals] = (this[$internals] = {
          accessors: {}
        });

        const accessors = internals.accessors;
        const prototype = this.prototype;

        function defineAccessor(_header) {
          const lHeader = normalizeHeader(_header);

          if (!accessors[lHeader]) {
            buildAccessors(prototype, _header);
            accessors[lHeader] = true;
          }
        }

        utils.isArray(header) ? header.forEach(defineAccessor) : defineAccessor(header);

        return this;
      }
    }

    AxiosHeaders.accessor(['Content-Type', 'Content-Length', 'Accept', 'Accept-Encoding', 'User-Agent', 'Authorization']);

    utils.freezeMethods(AxiosHeaders.prototype);
    utils.freezeMethods(AxiosHeaders);

    var AxiosHeaders$1 = AxiosHeaders;

    /**
     * Transform the data for a request or a response
     *
     * @param {Array|Function} fns A single function or Array of functions
     * @param {?Object} response The response object
     *
     * @returns {*} The resulting transformed data
     */
    function transformData(fns, response) {
      const config = this || defaults$1;
      const context = response || config;
      const headers = AxiosHeaders$1.from(context.headers);
      let data = context.data;

      utils.forEach(fns, function transform(fn) {
        data = fn.call(config, data, headers.normalize(), response ? response.status : undefined);
      });

      headers.normalize();

      return data;
    }

    function isCancel(value) {
      return !!(value && value.__CANCEL__);
    }

    /**
     * A `CanceledError` is an object that is thrown when an operation is canceled.
     *
     * @param {string=} message The message.
     * @param {Object=} config The config.
     * @param {Object=} request The request.
     *
     * @returns {CanceledError} The created error.
     */
    function CanceledError(message, config, request) {
      // eslint-disable-next-line no-eq-null,eqeqeq
      AxiosError.call(this, message == null ? 'canceled' : message, AxiosError.ERR_CANCELED, config, request);
      this.name = 'CanceledError';
    }

    utils.inherits(CanceledError, AxiosError, {
      __CANCEL__: true
    });

    /**
     * Resolve or reject a Promise based on response status.
     *
     * @param {Function} resolve A function that resolves the promise.
     * @param {Function} reject A function that rejects the promise.
     * @param {object} response The response.
     *
     * @returns {object} The response.
     */
    function settle(resolve, reject, response) {
      const validateStatus = response.config.validateStatus;
      if (!response.status || !validateStatus || validateStatus(response.status)) {
        resolve(response);
      } else {
        reject(new AxiosError(
          'Request failed with status code ' + response.status,
          [AxiosError.ERR_BAD_REQUEST, AxiosError.ERR_BAD_RESPONSE][Math.floor(response.status / 100) - 4],
          response.config,
          response.request,
          response
        ));
      }
    }

    var cookies = platform.isStandardBrowserEnv ?

    // Standard browser envs support document.cookie
      (function standardBrowserEnv() {
        return {
          write: function write(name, value, expires, path, domain, secure) {
            const cookie = [];
            cookie.push(name + '=' + encodeURIComponent(value));

            if (utils.isNumber(expires)) {
              cookie.push('expires=' + new Date(expires).toGMTString());
            }

            if (utils.isString(path)) {
              cookie.push('path=' + path);
            }

            if (utils.isString(domain)) {
              cookie.push('domain=' + domain);
            }

            if (secure === true) {
              cookie.push('secure');
            }

            document.cookie = cookie.join('; ');
          },

          read: function read(name) {
            const match = document.cookie.match(new RegExp('(^|;\\s*)(' + name + ')=([^;]*)'));
            return (match ? decodeURIComponent(match[3]) : null);
          },

          remove: function remove(name) {
            this.write(name, '', Date.now() - 86400000);
          }
        };
      })() :

    // Non standard browser env (web workers, react-native) lack needed support.
      (function nonStandardBrowserEnv() {
        return {
          write: function write() {},
          read: function read() { return null; },
          remove: function remove() {}
        };
      })();

    /**
     * Determines whether the specified URL is absolute
     *
     * @param {string} url The URL to test
     *
     * @returns {boolean} True if the specified URL is absolute, otherwise false
     */
    function isAbsoluteURL(url) {
      // A URL is considered absolute if it begins with "<scheme>://" or "//" (protocol-relative URL).
      // RFC 3986 defines scheme name as a sequence of characters beginning with a letter and followed
      // by any combination of letters, digits, plus, period, or hyphen.
      return /^([a-z][a-z\d+\-.]*:)?\/\//i.test(url);
    }

    /**
     * Creates a new URL by combining the specified URLs
     *
     * @param {string} baseURL The base URL
     * @param {string} relativeURL The relative URL
     *
     * @returns {string} The combined URL
     */
    function combineURLs(baseURL, relativeURL) {
      return relativeURL
        ? baseURL.replace(/\/+$/, '') + '/' + relativeURL.replace(/^\/+/, '')
        : baseURL;
    }

    /**
     * Creates a new URL by combining the baseURL with the requestedURL,
     * only when the requestedURL is not already an absolute URL.
     * If the requestURL is absolute, this function returns the requestedURL untouched.
     *
     * @param {string} baseURL The base URL
     * @param {string} requestedURL Absolute or relative URL to combine
     *
     * @returns {string} The combined full path
     */
    function buildFullPath(baseURL, requestedURL) {
      if (baseURL && !isAbsoluteURL(requestedURL)) {
        return combineURLs(baseURL, requestedURL);
      }
      return requestedURL;
    }

    var isURLSameOrigin = platform.isStandardBrowserEnv ?

    // Standard browser envs have full support of the APIs needed to test
    // whether the request URL is of the same origin as current location.
      (function standardBrowserEnv() {
        const msie = /(msie|trident)/i.test(navigator.userAgent);
        const urlParsingNode = document.createElement('a');
        let originURL;

        /**
        * Parse a URL to discover it's components
        *
        * @param {String} url The URL to be parsed
        * @returns {Object}
        */
        function resolveURL(url) {
          let href = url;

          if (msie) {
            // IE needs attribute set twice to normalize properties
            urlParsingNode.setAttribute('href', href);
            href = urlParsingNode.href;
          }

          urlParsingNode.setAttribute('href', href);

          // urlParsingNode provides the UrlUtils interface - http://url.spec.whatwg.org/#urlutils
          return {
            href: urlParsingNode.href,
            protocol: urlParsingNode.protocol ? urlParsingNode.protocol.replace(/:$/, '') : '',
            host: urlParsingNode.host,
            search: urlParsingNode.search ? urlParsingNode.search.replace(/^\?/, '') : '',
            hash: urlParsingNode.hash ? urlParsingNode.hash.replace(/^#/, '') : '',
            hostname: urlParsingNode.hostname,
            port: urlParsingNode.port,
            pathname: (urlParsingNode.pathname.charAt(0) === '/') ?
              urlParsingNode.pathname :
              '/' + urlParsingNode.pathname
          };
        }

        originURL = resolveURL(window.location.href);

        /**
        * Determine if a URL shares the same origin as the current location
        *
        * @param {String} requestURL The URL to test
        * @returns {boolean} True if URL shares the same origin, otherwise false
        */
        return function isURLSameOrigin(requestURL) {
          const parsed = (utils.isString(requestURL)) ? resolveURL(requestURL) : requestURL;
          return (parsed.protocol === originURL.protocol &&
              parsed.host === originURL.host);
        };
      })() :

      // Non standard browser envs (web workers, react-native) lack needed support.
      (function nonStandardBrowserEnv() {
        return function isURLSameOrigin() {
          return true;
        };
      })();

    function parseProtocol(url) {
      const match = /^([-+\w]{1,25})(:?\/\/|:)/.exec(url);
      return match && match[1] || '';
    }

    /**
     * Calculate data maxRate
     * @param {Number} [samplesCount= 10]
     * @param {Number} [min= 1000]
     * @returns {Function}
     */
    function speedometer(samplesCount, min) {
      samplesCount = samplesCount || 10;
      const bytes = new Array(samplesCount);
      const timestamps = new Array(samplesCount);
      let head = 0;
      let tail = 0;
      let firstSampleTS;

      min = min !== undefined ? min : 1000;

      return function push(chunkLength) {
        const now = Date.now();

        const startedAt = timestamps[tail];

        if (!firstSampleTS) {
          firstSampleTS = now;
        }

        bytes[head] = chunkLength;
        timestamps[head] = now;

        let i = tail;
        let bytesCount = 0;

        while (i !== head) {
          bytesCount += bytes[i++];
          i = i % samplesCount;
        }

        head = (head + 1) % samplesCount;

        if (head === tail) {
          tail = (tail + 1) % samplesCount;
        }

        if (now - firstSampleTS < min) {
          return;
        }

        const passed = startedAt && now - startedAt;

        return passed ? Math.round(bytesCount * 1000 / passed) : undefined;
      };
    }

    function progressEventReducer(listener, isDownloadStream) {
      let bytesNotified = 0;
      const _speedometer = speedometer(50, 250);

      return e => {
        const loaded = e.loaded;
        const total = e.lengthComputable ? e.total : undefined;
        const progressBytes = loaded - bytesNotified;
        const rate = _speedometer(progressBytes);
        const inRange = loaded <= total;

        bytesNotified = loaded;

        const data = {
          loaded,
          total,
          progress: total ? (loaded / total) : undefined,
          bytes: progressBytes,
          rate: rate ? rate : undefined,
          estimated: rate && total && inRange ? (total - loaded) / rate : undefined,
          event: e
        };

        data[isDownloadStream ? 'download' : 'upload'] = true;

        listener(data);
      };
    }

    const isXHRAdapterSupported = typeof XMLHttpRequest !== 'undefined';

    var xhrAdapter = isXHRAdapterSupported && function (config) {
      return new Promise(function dispatchXhrRequest(resolve, reject) {
        let requestData = config.data;
        const requestHeaders = AxiosHeaders$1.from(config.headers).normalize();
        const responseType = config.responseType;
        let onCanceled;
        function done() {
          if (config.cancelToken) {
            config.cancelToken.unsubscribe(onCanceled);
          }

          if (config.signal) {
            config.signal.removeEventListener('abort', onCanceled);
          }
        }

        if (utils.isFormData(requestData)) {
          if (platform.isStandardBrowserEnv || platform.isStandardBrowserWebWorkerEnv) {
            requestHeaders.setContentType(false); // Let the browser set it
          } else {
            requestHeaders.setContentType('multipart/form-data;', false); // mobile/desktop app frameworks
          }
        }

        let request = new XMLHttpRequest();

        // HTTP basic authentication
        if (config.auth) {
          const username = config.auth.username || '';
          const password = config.auth.password ? unescape(encodeURIComponent(config.auth.password)) : '';
          requestHeaders.set('Authorization', 'Basic ' + btoa(username + ':' + password));
        }

        const fullPath = buildFullPath(config.baseURL, config.url);

        request.open(config.method.toUpperCase(), buildURL(fullPath, config.params, config.paramsSerializer), true);

        // Set the request timeout in MS
        request.timeout = config.timeout;

        function onloadend() {
          if (!request) {
            return;
          }
          // Prepare the response
          const responseHeaders = AxiosHeaders$1.from(
            'getAllResponseHeaders' in request && request.getAllResponseHeaders()
          );
          const responseData = !responseType || responseType === 'text' || responseType === 'json' ?
            request.responseText : request.response;
          const response = {
            data: responseData,
            status: request.status,
            statusText: request.statusText,
            headers: responseHeaders,
            config,
            request
          };

          settle(function _resolve(value) {
            resolve(value);
            done();
          }, function _reject(err) {
            reject(err);
            done();
          }, response);

          // Clean up request
          request = null;
        }

        if ('onloadend' in request) {
          // Use onloadend if available
          request.onloadend = onloadend;
        } else {
          // Listen for ready state to emulate onloadend
          request.onreadystatechange = function handleLoad() {
            if (!request || request.readyState !== 4) {
              return;
            }

            // The request errored out and we didn't get a response, this will be
            // handled by onerror instead
            // With one exception: request that using file: protocol, most browsers
            // will return status as 0 even though it's a successful request
            if (request.status === 0 && !(request.responseURL && request.responseURL.indexOf('file:') === 0)) {
              return;
            }
            // readystate handler is calling before onerror or ontimeout handlers,
            // so we should call onloadend on the next 'tick'
            setTimeout(onloadend);
          };
        }

        // Handle browser request cancellation (as opposed to a manual cancellation)
        request.onabort = function handleAbort() {
          if (!request) {
            return;
          }

          reject(new AxiosError('Request aborted', AxiosError.ECONNABORTED, config, request));

          // Clean up request
          request = null;
        };

        // Handle low level network errors
        request.onerror = function handleError() {
          // Real errors are hidden from us by the browser
          // onerror should only fire if it's a network error
          reject(new AxiosError('Network Error', AxiosError.ERR_NETWORK, config, request));

          // Clean up request
          request = null;
        };

        // Handle timeout
        request.ontimeout = function handleTimeout() {
          let timeoutErrorMessage = config.timeout ? 'timeout of ' + config.timeout + 'ms exceeded' : 'timeout exceeded';
          const transitional = config.transitional || transitionalDefaults;
          if (config.timeoutErrorMessage) {
            timeoutErrorMessage = config.timeoutErrorMessage;
          }
          reject(new AxiosError(
            timeoutErrorMessage,
            transitional.clarifyTimeoutError ? AxiosError.ETIMEDOUT : AxiosError.ECONNABORTED,
            config,
            request));

          // Clean up request
          request = null;
        };

        // Add xsrf header
        // This is only done if running in a standard browser environment.
        // Specifically not if we're in a web worker, or react-native.
        if (platform.isStandardBrowserEnv) {
          // Add xsrf header
          const xsrfValue = (config.withCredentials || isURLSameOrigin(fullPath))
            && config.xsrfCookieName && cookies.read(config.xsrfCookieName);

          if (xsrfValue) {
            requestHeaders.set(config.xsrfHeaderName, xsrfValue);
          }
        }

        // Remove Content-Type if data is undefined
        requestData === undefined && requestHeaders.setContentType(null);

        // Add headers to the request
        if ('setRequestHeader' in request) {
          utils.forEach(requestHeaders.toJSON(), function setRequestHeader(val, key) {
            request.setRequestHeader(key, val);
          });
        }

        // Add withCredentials to request if needed
        if (!utils.isUndefined(config.withCredentials)) {
          request.withCredentials = !!config.withCredentials;
        }

        // Add responseType to request if needed
        if (responseType && responseType !== 'json') {
          request.responseType = config.responseType;
        }

        // Handle progress if needed
        if (typeof config.onDownloadProgress === 'function') {
          request.addEventListener('progress', progressEventReducer(config.onDownloadProgress, true));
        }

        // Not all browsers support upload events
        if (typeof config.onUploadProgress === 'function' && request.upload) {
          request.upload.addEventListener('progress', progressEventReducer(config.onUploadProgress));
        }

        if (config.cancelToken || config.signal) {
          // Handle cancellation
          // eslint-disable-next-line func-names
          onCanceled = cancel => {
            if (!request) {
              return;
            }
            reject(!cancel || cancel.type ? new CanceledError(null, config, request) : cancel);
            request.abort();
            request = null;
          };

          config.cancelToken && config.cancelToken.subscribe(onCanceled);
          if (config.signal) {
            config.signal.aborted ? onCanceled() : config.signal.addEventListener('abort', onCanceled);
          }
        }

        const protocol = parseProtocol(fullPath);

        if (protocol && platform.protocols.indexOf(protocol) === -1) {
          reject(new AxiosError('Unsupported protocol ' + protocol + ':', AxiosError.ERR_BAD_REQUEST, config));
          return;
        }


        // Send the request
        request.send(requestData || null);
      });
    };

    const knownAdapters = {
      http: httpAdapter,
      xhr: xhrAdapter
    };

    utils.forEach(knownAdapters, (fn, value) => {
      if(fn) {
        try {
          Object.defineProperty(fn, 'name', {value});
        } catch (e) {
          // eslint-disable-next-line no-empty
        }
        Object.defineProperty(fn, 'adapterName', {value});
      }
    });

    var adapters = {
      getAdapter: (adapters) => {
        adapters = utils.isArray(adapters) ? adapters : [adapters];

        const {length} = adapters;
        let nameOrAdapter;
        let adapter;

        for (let i = 0; i < length; i++) {
          nameOrAdapter = adapters[i];
          if((adapter = utils.isString(nameOrAdapter) ? knownAdapters[nameOrAdapter.toLowerCase()] : nameOrAdapter)) {
            break;
          }
        }

        if (!adapter) {
          if (adapter === false) {
            throw new AxiosError(
              `Adapter ${nameOrAdapter} is not supported by the environment`,
              'ERR_NOT_SUPPORT'
            );
          }

          throw new Error(
            utils.hasOwnProp(knownAdapters, nameOrAdapter) ?
              `Adapter '${nameOrAdapter}' is not available in the build` :
              `Unknown adapter '${nameOrAdapter}'`
          );
        }

        if (!utils.isFunction(adapter)) {
          throw new TypeError('adapter is not a function');
        }

        return adapter;
      },
      adapters: knownAdapters
    };

    /**
     * Throws a `CanceledError` if cancellation has been requested.
     *
     * @param {Object} config The config that is to be used for the request
     *
     * @returns {void}
     */
    function throwIfCancellationRequested(config) {
      if (config.cancelToken) {
        config.cancelToken.throwIfRequested();
      }

      if (config.signal && config.signal.aborted) {
        throw new CanceledError(null, config);
      }
    }

    /**
     * Dispatch a request to the server using the configured adapter.
     *
     * @param {object} config The config that is to be used for the request
     *
     * @returns {Promise} The Promise to be fulfilled
     */
    function dispatchRequest(config) {
      throwIfCancellationRequested(config);

      config.headers = AxiosHeaders$1.from(config.headers);

      // Transform request data
      config.data = transformData.call(
        config,
        config.transformRequest
      );

      if (['post', 'put', 'patch'].indexOf(config.method) !== -1) {
        config.headers.setContentType('application/x-www-form-urlencoded', false);
      }

      const adapter = adapters.getAdapter(config.adapter || defaults$1.adapter);

      return adapter(config).then(function onAdapterResolution(response) {
        throwIfCancellationRequested(config);

        // Transform response data
        response.data = transformData.call(
          config,
          config.transformResponse,
          response
        );

        response.headers = AxiosHeaders$1.from(response.headers);

        return response;
      }, function onAdapterRejection(reason) {
        if (!isCancel(reason)) {
          throwIfCancellationRequested(config);

          // Transform response data
          if (reason && reason.response) {
            reason.response.data = transformData.call(
              config,
              config.transformResponse,
              reason.response
            );
            reason.response.headers = AxiosHeaders$1.from(reason.response.headers);
          }
        }

        return Promise.reject(reason);
      });
    }

    const headersToObject = (thing) => thing instanceof AxiosHeaders$1 ? thing.toJSON() : thing;

    /**
     * Config-specific merge-function which creates a new config-object
     * by merging two configuration objects together.
     *
     * @param {Object} config1
     * @param {Object} config2
     *
     * @returns {Object} New object resulting from merging config2 to config1
     */
    function mergeConfig(config1, config2) {
      // eslint-disable-next-line no-param-reassign
      config2 = config2 || {};
      const config = {};

      function getMergedValue(target, source, caseless) {
        if (utils.isPlainObject(target) && utils.isPlainObject(source)) {
          return utils.merge.call({caseless}, target, source);
        } else if (utils.isPlainObject(source)) {
          return utils.merge({}, source);
        } else if (utils.isArray(source)) {
          return source.slice();
        }
        return source;
      }

      // eslint-disable-next-line consistent-return
      function mergeDeepProperties(a, b, caseless) {
        if (!utils.isUndefined(b)) {
          return getMergedValue(a, b, caseless);
        } else if (!utils.isUndefined(a)) {
          return getMergedValue(undefined, a, caseless);
        }
      }

      // eslint-disable-next-line consistent-return
      function valueFromConfig2(a, b) {
        if (!utils.isUndefined(b)) {
          return getMergedValue(undefined, b);
        }
      }

      // eslint-disable-next-line consistent-return
      function defaultToConfig2(a, b) {
        if (!utils.isUndefined(b)) {
          return getMergedValue(undefined, b);
        } else if (!utils.isUndefined(a)) {
          return getMergedValue(undefined, a);
        }
      }

      // eslint-disable-next-line consistent-return
      function mergeDirectKeys(a, b, prop) {
        if (prop in config2) {
          return getMergedValue(a, b);
        } else if (prop in config1) {
          return getMergedValue(undefined, a);
        }
      }

      const mergeMap = {
        url: valueFromConfig2,
        method: valueFromConfig2,
        data: valueFromConfig2,
        baseURL: defaultToConfig2,
        transformRequest: defaultToConfig2,
        transformResponse: defaultToConfig2,
        paramsSerializer: defaultToConfig2,
        timeout: defaultToConfig2,
        timeoutMessage: defaultToConfig2,
        withCredentials: defaultToConfig2,
        adapter: defaultToConfig2,
        responseType: defaultToConfig2,
        xsrfCookieName: defaultToConfig2,
        xsrfHeaderName: defaultToConfig2,
        onUploadProgress: defaultToConfig2,
        onDownloadProgress: defaultToConfig2,
        decompress: defaultToConfig2,
        maxContentLength: defaultToConfig2,
        maxBodyLength: defaultToConfig2,
        beforeRedirect: defaultToConfig2,
        transport: defaultToConfig2,
        httpAgent: defaultToConfig2,
        httpsAgent: defaultToConfig2,
        cancelToken: defaultToConfig2,
        socketPath: defaultToConfig2,
        responseEncoding: defaultToConfig2,
        validateStatus: mergeDirectKeys,
        headers: (a, b) => mergeDeepProperties(headersToObject(a), headersToObject(b), true)
      };

      utils.forEach(Object.keys(Object.assign({}, config1, config2)), function computeConfigValue(prop) {
        const merge = mergeMap[prop] || mergeDeepProperties;
        const configValue = merge(config1[prop], config2[prop], prop);
        (utils.isUndefined(configValue) && merge !== mergeDirectKeys) || (config[prop] = configValue);
      });

      return config;
    }

    const VERSION = "1.4.0";

    const validators$1 = {};

    // eslint-disable-next-line func-names
    ['object', 'boolean', 'number', 'function', 'string', 'symbol'].forEach((type, i) => {
      validators$1[type] = function validator(thing) {
        return typeof thing === type || 'a' + (i < 1 ? 'n ' : ' ') + type;
      };
    });

    const deprecatedWarnings = {};

    /**
     * Transitional option validator
     *
     * @param {function|boolean?} validator - set to false if the transitional option has been removed
     * @param {string?} version - deprecated version / removed since version
     * @param {string?} message - some message with additional info
     *
     * @returns {function}
     */
    validators$1.transitional = function transitional(validator, version, message) {
      function formatMessage(opt, desc) {
        return '[Axios v' + VERSION + '] Transitional option \'' + opt + '\'' + desc + (message ? '. ' + message : '');
      }

      // eslint-disable-next-line func-names
      return (value, opt, opts) => {
        if (validator === false) {
          throw new AxiosError(
            formatMessage(opt, ' has been removed' + (version ? ' in ' + version : '')),
            AxiosError.ERR_DEPRECATED
          );
        }

        if (version && !deprecatedWarnings[opt]) {
          deprecatedWarnings[opt] = true;
          // eslint-disable-next-line no-console
          console.warn(
            formatMessage(
              opt,
              ' has been deprecated since v' + version + ' and will be removed in the near future'
            )
          );
        }

        return validator ? validator(value, opt, opts) : true;
      };
    };

    /**
     * Assert object's properties type
     *
     * @param {object} options
     * @param {object} schema
     * @param {boolean?} allowUnknown
     *
     * @returns {object}
     */

    function assertOptions(options, schema, allowUnknown) {
      if (typeof options !== 'object') {
        throw new AxiosError('options must be an object', AxiosError.ERR_BAD_OPTION_VALUE);
      }
      const keys = Object.keys(options);
      let i = keys.length;
      while (i-- > 0) {
        const opt = keys[i];
        const validator = schema[opt];
        if (validator) {
          const value = options[opt];
          const result = value === undefined || validator(value, opt, options);
          if (result !== true) {
            throw new AxiosError('option ' + opt + ' must be ' + result, AxiosError.ERR_BAD_OPTION_VALUE);
          }
          continue;
        }
        if (allowUnknown !== true) {
          throw new AxiosError('Unknown option ' + opt, AxiosError.ERR_BAD_OPTION);
        }
      }
    }

    var validator = {
      assertOptions,
      validators: validators$1
    };

    const validators = validator.validators;

    /**
     * Create a new instance of Axios
     *
     * @param {Object} instanceConfig The default config for the instance
     *
     * @return {Axios} A new instance of Axios
     */
    class Axios {
      constructor(instanceConfig) {
        this.defaults = instanceConfig;
        this.interceptors = {
          request: new InterceptorManager$1(),
          response: new InterceptorManager$1()
        };
      }

      /**
       * Dispatch a request
       *
       * @param {String|Object} configOrUrl The config specific for this request (merged with this.defaults)
       * @param {?Object} config
       *
       * @returns {Promise} The Promise to be fulfilled
       */
      request(configOrUrl, config) {
        /*eslint no-param-reassign:0*/
        // Allow for axios('example/url'[, config]) a la fetch API
        if (typeof configOrUrl === 'string') {
          config = config || {};
          config.url = configOrUrl;
        } else {
          config = configOrUrl || {};
        }

        config = mergeConfig(this.defaults, config);

        const {transitional, paramsSerializer, headers} = config;

        if (transitional !== undefined) {
          validator.assertOptions(transitional, {
            silentJSONParsing: validators.transitional(validators.boolean),
            forcedJSONParsing: validators.transitional(validators.boolean),
            clarifyTimeoutError: validators.transitional(validators.boolean)
          }, false);
        }

        if (paramsSerializer != null) {
          if (utils.isFunction(paramsSerializer)) {
            config.paramsSerializer = {
              serialize: paramsSerializer
            };
          } else {
            validator.assertOptions(paramsSerializer, {
              encode: validators.function,
              serialize: validators.function
            }, true);
          }
        }

        // Set config.method
        config.method = (config.method || this.defaults.method || 'get').toLowerCase();

        let contextHeaders;

        // Flatten headers
        contextHeaders = headers && utils.merge(
          headers.common,
          headers[config.method]
        );

        contextHeaders && utils.forEach(
          ['delete', 'get', 'head', 'post', 'put', 'patch', 'common'],
          (method) => {
            delete headers[method];
          }
        );

        config.headers = AxiosHeaders$1.concat(contextHeaders, headers);

        // filter out skipped interceptors
        const requestInterceptorChain = [];
        let synchronousRequestInterceptors = true;
        this.interceptors.request.forEach(function unshiftRequestInterceptors(interceptor) {
          if (typeof interceptor.runWhen === 'function' && interceptor.runWhen(config) === false) {
            return;
          }

          synchronousRequestInterceptors = synchronousRequestInterceptors && interceptor.synchronous;

          requestInterceptorChain.unshift(interceptor.fulfilled, interceptor.rejected);
        });

        const responseInterceptorChain = [];
        this.interceptors.response.forEach(function pushResponseInterceptors(interceptor) {
          responseInterceptorChain.push(interceptor.fulfilled, interceptor.rejected);
        });

        let promise;
        let i = 0;
        let len;

        if (!synchronousRequestInterceptors) {
          const chain = [dispatchRequest.bind(this), undefined];
          chain.unshift.apply(chain, requestInterceptorChain);
          chain.push.apply(chain, responseInterceptorChain);
          len = chain.length;

          promise = Promise.resolve(config);

          while (i < len) {
            promise = promise.then(chain[i++], chain[i++]);
          }

          return promise;
        }

        len = requestInterceptorChain.length;

        let newConfig = config;

        i = 0;

        while (i < len) {
          const onFulfilled = requestInterceptorChain[i++];
          const onRejected = requestInterceptorChain[i++];
          try {
            newConfig = onFulfilled(newConfig);
          } catch (error) {
            onRejected.call(this, error);
            break;
          }
        }

        try {
          promise = dispatchRequest.call(this, newConfig);
        } catch (error) {
          return Promise.reject(error);
        }

        i = 0;
        len = responseInterceptorChain.length;

        while (i < len) {
          promise = promise.then(responseInterceptorChain[i++], responseInterceptorChain[i++]);
        }

        return promise;
      }

      getUri(config) {
        config = mergeConfig(this.defaults, config);
        const fullPath = buildFullPath(config.baseURL, config.url);
        return buildURL(fullPath, config.params, config.paramsSerializer);
      }
    }

    // Provide aliases for supported request methods
    utils.forEach(['delete', 'get', 'head', 'options'], function forEachMethodNoData(method) {
      /*eslint func-names:0*/
      Axios.prototype[method] = function(url, config) {
        return this.request(mergeConfig(config || {}, {
          method,
          url,
          data: (config || {}).data
        }));
      };
    });

    utils.forEach(['post', 'put', 'patch'], function forEachMethodWithData(method) {
      /*eslint func-names:0*/

      function generateHTTPMethod(isForm) {
        return function httpMethod(url, data, config) {
          return this.request(mergeConfig(config || {}, {
            method,
            headers: isForm ? {
              'Content-Type': 'multipart/form-data'
            } : {},
            url,
            data
          }));
        };
      }

      Axios.prototype[method] = generateHTTPMethod();

      Axios.prototype[method + 'Form'] = generateHTTPMethod(true);
    });

    var Axios$1 = Axios;

    /**
     * A `CancelToken` is an object that can be used to request cancellation of an operation.
     *
     * @param {Function} executor The executor function.
     *
     * @returns {CancelToken}
     */
    class CancelToken {
      constructor(executor) {
        if (typeof executor !== 'function') {
          throw new TypeError('executor must be a function.');
        }

        let resolvePromise;

        this.promise = new Promise(function promiseExecutor(resolve) {
          resolvePromise = resolve;
        });

        const token = this;

        // eslint-disable-next-line func-names
        this.promise.then(cancel => {
          if (!token._listeners) return;

          let i = token._listeners.length;

          while (i-- > 0) {
            token._listeners[i](cancel);
          }
          token._listeners = null;
        });

        // eslint-disable-next-line func-names
        this.promise.then = onfulfilled => {
          let _resolve;
          // eslint-disable-next-line func-names
          const promise = new Promise(resolve => {
            token.subscribe(resolve);
            _resolve = resolve;
          }).then(onfulfilled);

          promise.cancel = function reject() {
            token.unsubscribe(_resolve);
          };

          return promise;
        };

        executor(function cancel(message, config, request) {
          if (token.reason) {
            // Cancellation has already been requested
            return;
          }

          token.reason = new CanceledError(message, config, request);
          resolvePromise(token.reason);
        });
      }

      /**
       * Throws a `CanceledError` if cancellation has been requested.
       */
      throwIfRequested() {
        if (this.reason) {
          throw this.reason;
        }
      }

      /**
       * Subscribe to the cancel signal
       */

      subscribe(listener) {
        if (this.reason) {
          listener(this.reason);
          return;
        }

        if (this._listeners) {
          this._listeners.push(listener);
        } else {
          this._listeners = [listener];
        }
      }

      /**
       * Unsubscribe from the cancel signal
       */

      unsubscribe(listener) {
        if (!this._listeners) {
          return;
        }
        const index = this._listeners.indexOf(listener);
        if (index !== -1) {
          this._listeners.splice(index, 1);
        }
      }

      /**
       * Returns an object that contains a new `CancelToken` and a function that, when called,
       * cancels the `CancelToken`.
       */
      static source() {
        let cancel;
        const token = new CancelToken(function executor(c) {
          cancel = c;
        });
        return {
          token,
          cancel
        };
      }
    }

    var CancelToken$1 = CancelToken;

    /**
     * Syntactic sugar for invoking a function and expanding an array for arguments.
     *
     * Common use case would be to use `Function.prototype.apply`.
     *
     *  ```js
     *  function f(x, y, z) {}
     *  var args = [1, 2, 3];
     *  f.apply(null, args);
     *  ```
     *
     * With `spread` this example can be re-written.
     *
     *  ```js
     *  spread(function(x, y, z) {})([1, 2, 3]);
     *  ```
     *
     * @param {Function} callback
     *
     * @returns {Function}
     */
    function spread(callback) {
      return function wrap(arr) {
        return callback.apply(null, arr);
      };
    }

    /**
     * Determines whether the payload is an error thrown by Axios
     *
     * @param {*} payload The value to test
     *
     * @returns {boolean} True if the payload is an error thrown by Axios, otherwise false
     */
    function isAxiosError(payload) {
      return utils.isObject(payload) && (payload.isAxiosError === true);
    }

    const HttpStatusCode = {
      Continue: 100,
      SwitchingProtocols: 101,
      Processing: 102,
      EarlyHints: 103,
      Ok: 200,
      Created: 201,
      Accepted: 202,
      NonAuthoritativeInformation: 203,
      NoContent: 204,
      ResetContent: 205,
      PartialContent: 206,
      MultiStatus: 207,
      AlreadyReported: 208,
      ImUsed: 226,
      MultipleChoices: 300,
      MovedPermanently: 301,
      Found: 302,
      SeeOther: 303,
      NotModified: 304,
      UseProxy: 305,
      Unused: 306,
      TemporaryRedirect: 307,
      PermanentRedirect: 308,
      BadRequest: 400,
      Unauthorized: 401,
      PaymentRequired: 402,
      Forbidden: 403,
      NotFound: 404,
      MethodNotAllowed: 405,
      NotAcceptable: 406,
      ProxyAuthenticationRequired: 407,
      RequestTimeout: 408,
      Conflict: 409,
      Gone: 410,
      LengthRequired: 411,
      PreconditionFailed: 412,
      PayloadTooLarge: 413,
      UriTooLong: 414,
      UnsupportedMediaType: 415,
      RangeNotSatisfiable: 416,
      ExpectationFailed: 417,
      ImATeapot: 418,
      MisdirectedRequest: 421,
      UnprocessableEntity: 422,
      Locked: 423,
      FailedDependency: 424,
      TooEarly: 425,
      UpgradeRequired: 426,
      PreconditionRequired: 428,
      TooManyRequests: 429,
      RequestHeaderFieldsTooLarge: 431,
      UnavailableForLegalReasons: 451,
      InternalServerError: 500,
      NotImplemented: 501,
      BadGateway: 502,
      ServiceUnavailable: 503,
      GatewayTimeout: 504,
      HttpVersionNotSupported: 505,
      VariantAlsoNegotiates: 506,
      InsufficientStorage: 507,
      LoopDetected: 508,
      NotExtended: 510,
      NetworkAuthenticationRequired: 511,
    };

    Object.entries(HttpStatusCode).forEach(([key, value]) => {
      HttpStatusCode[value] = key;
    });

    var HttpStatusCode$1 = HttpStatusCode;

    /**
     * Create an instance of Axios
     *
     * @param {Object} defaultConfig The default config for the instance
     *
     * @returns {Axios} A new instance of Axios
     */
    function createInstance(defaultConfig) {
      const context = new Axios$1(defaultConfig);
      const instance = bind(Axios$1.prototype.request, context);

      // Copy axios.prototype to instance
      utils.extend(instance, Axios$1.prototype, context, {allOwnKeys: true});

      // Copy context to instance
      utils.extend(instance, context, null, {allOwnKeys: true});

      // Factory for creating new instances
      instance.create = function create(instanceConfig) {
        return createInstance(mergeConfig(defaultConfig, instanceConfig));
      };

      return instance;
    }

    // Create the default instance to be exported
    const axios = createInstance(defaults$1);

    // Expose Axios class to allow class inheritance
    axios.Axios = Axios$1;

    // Expose Cancel & CancelToken
    axios.CanceledError = CanceledError;
    axios.CancelToken = CancelToken$1;
    axios.isCancel = isCancel;
    axios.VERSION = VERSION;
    axios.toFormData = toFormData;

    // Expose AxiosError class
    axios.AxiosError = AxiosError;

    // alias for CanceledError for backward compatibility
    axios.Cancel = axios.CanceledError;

    // Expose all/spread
    axios.all = function all(promises) {
      return Promise.all(promises);
    };

    axios.spread = spread;

    // Expose isAxiosError
    axios.isAxiosError = isAxiosError;

    // Expose mergeConfig
    axios.mergeConfig = mergeConfig;

    axios.AxiosHeaders = AxiosHeaders$1;

    axios.formToJSON = thing => formDataToJSON(utils.isHTMLForm(thing) ? new FormData(thing) : thing);

    axios.HttpStatusCode = HttpStatusCode$1;

    axios.default = axios;

    // this module should only have a default export
    var axios$1 = axios;

    /* src/component/dashboard/Dashboard.svelte generated by Svelte v3.59.1 */

    const { console: console_1$6 } = globals;
    const file$8 = "src/component/dashboard/Dashboard.svelte";

    function get_each_context$3(ctx, list, i) {
    	const child_ctx = ctx.slice();
    	child_ctx[49] = list[i];
    	return child_ctx;
    }

    // (307:3) {:else}
    function create_else_block_1$2(ctx) {
    	let div0;
    	let img_1;
    	let img_1_src_value;
    	let t0;
    	let h2;
    	let t1;
    	let span;
    	let connectstatus;
    	let t2;
    	let div1;
    	let button0;
    	let t4;
    	let button1;
    	let t6;
    	let button2;
    	let t7_value = (/*blocked*/ ctx[8] ? 'Unblock' : 'Block') + "";
    	let t7;
    	let t8;
    	let button3;
    	let t10;
    	let button4;
    	let current;
    	let mounted;
    	let dispose;

    	connectstatus = new ConnectStatus({
    			props: { userId: /*targetId*/ ctx[0] },
    			$$inline: true
    		});

    	const block = {
    		c: function create() {
    			div0 = element("div");
    			img_1 = element("img");
    			t0 = space();
    			h2 = element("h2");
    			t1 = text(/*targetName*/ ctx[4]);
    			span = element("span");
    			create_component(connectstatus.$$.fragment);
    			t2 = space();
    			div1 = element("div");
    			button0 = element("button");
    			button0.textContent = "←";
    			t4 = space();
    			button1 = element("button");
    			button1.textContent = "Add Friend";
    			t6 = space();
    			button2 = element("button");
    			t7 = text(t7_value);
    			t8 = space();
    			button3 = element("button");
    			button3.textContent = "Send Msg";
    			t10 = space();
    			button4 = element("button");
    			button4.textContent = "Play";
    			if (!src_url_equal(img_1.src, img_1_src_value = /*targetImg*/ ctx[5])) attr_dev(img_1, "src", img_1_src_value);
    			attr_dev(img_1, "alt", "Avatar");
    			attr_dev(img_1, "class", "svelte-191atea");
    			add_location(img_1, file$8, 309, 10, 7587);
    			attr_dev(div0, "class", "avatar svelte-191atea");
    			add_location(div0, file$8, 307, 7, 7500);
    			set_style(span, "margin-left", "10px");
    			add_location(span, file$8, 312, 17, 7725);
    			attr_dev(h2, "class", "shiny-text svelte-191atea");
    			set_style(h2, "display", "flex");
    			set_style(h2, "align-items", "center");
    			add_location(h2, file$8, 311, 4, 7640);
    			attr_dev(button0, "class", "button-profile svelte-191atea");
    			add_location(button0, file$8, 315, 8, 7854);
    			attr_dev(button1, "class", "button-profile svelte-191atea");
    			add_location(button1, file$8, 316, 8, 7938);
    			attr_dev(button2, "class", "button-profile block-button svelte-191atea");
    			toggle_class(button2, "active", !/*blocked*/ ctx[8]);
    			toggle_class(button2, "inactive", /*blocked*/ ctx[8]);
    			add_location(button2, file$8, 317, 5, 8031);
    			attr_dev(button3, "class", "button-profile svelte-191atea");
    			add_location(button3, file$8, 332, 8, 8389);
    			attr_dev(button4, "class", "button-profile svelte-191atea");
    			add_location(button4, file$8, 333, 8, 8476);
    			attr_dev(div1, "class", "button-container svelte-191atea");
    			add_location(div1, file$8, 314, 4, 7815);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div0, anchor);
    			append_dev(div0, img_1);
    			insert_dev(target, t0, anchor);
    			insert_dev(target, h2, anchor);
    			append_dev(h2, t1);
    			append_dev(h2, span);
    			mount_component(connectstatus, span, null);
    			insert_dev(target, t2, anchor);
    			insert_dev(target, div1, anchor);
    			append_dev(div1, button0);
    			append_dev(div1, t4);
    			append_dev(div1, button1);
    			append_dev(div1, t6);
    			append_dev(div1, button2);
    			append_dev(button2, t7);
    			append_dev(div1, t8);
    			append_dev(div1, button3);
    			append_dev(div1, t10);
    			append_dev(div1, button4);
    			current = true;

    			if (!mounted) {
    				dispose = [
    					listen_dev(button0, "click", /*click_handler_5*/ ctx[33], false, false, false, false),
    					listen_dev(button1, "click", /*click_handler_6*/ ctx[34], false, false, false, false),
    					listen_dev(button2, "click", /*click_handler_7*/ ctx[35], false, false, false, false),
    					listen_dev(button3, "click", /*click_handler_8*/ ctx[36], false, false, false, false),
    					listen_dev(button4, "click", /*sendInvitation*/ ctx[25], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (!current || dirty[0] & /*targetImg*/ 32 && !src_url_equal(img_1.src, img_1_src_value = /*targetImg*/ ctx[5])) {
    				attr_dev(img_1, "src", img_1_src_value);
    			}

    			if (!current || dirty[0] & /*targetName*/ 16) set_data_dev(t1, /*targetName*/ ctx[4]);
    			const connectstatus_changes = {};
    			if (dirty[0] & /*targetId*/ 1) connectstatus_changes.userId = /*targetId*/ ctx[0];
    			connectstatus.$set(connectstatus_changes);
    			if ((!current || dirty[0] & /*blocked*/ 256) && t7_value !== (t7_value = (/*blocked*/ ctx[8] ? 'Unblock' : 'Block') + "")) set_data_dev(t7, t7_value);

    			if (!current || dirty[0] & /*blocked*/ 256) {
    				toggle_class(button2, "active", !/*blocked*/ ctx[8]);
    			}

    			if (!current || dirty[0] & /*blocked*/ 256) {
    				toggle_class(button2, "inactive", /*blocked*/ ctx[8]);
    			}
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(connectstatus.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(connectstatus.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div0);
    			if (detaching) detach_dev(t0);
    			if (detaching) detach_dev(h2);
    			destroy_component(connectstatus);
    			if (detaching) detach_dev(t2);
    			if (detaching) detach_dev(div1);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block_1$2.name,
    		type: "else",
    		source: "(307:3) {:else}",
    		ctx
    	});

    	return block;
    }

    // (290:3) {#if targetId === id}
    function create_if_block_4$3(ctx) {
    	let h2;
    	let t0;
    	let t1;
    	let div;
    	let button0;
    	let t3;
    	let button1;
    	let t5;
    	let button2;
    	let t7;
    	let mounted;
    	let dispose;
    	let if_block = /*qrCodeImageUrl*/ ctx[9] && create_if_block_5$2(ctx);

    	const block = {
    		c: function create() {
    			h2 = element("h2");
    			t0 = text(/*name*/ ctx[2]);
    			t1 = space();
    			div = element("div");
    			button0 = element("button");
    			button0.textContent = "Update";
    			t3 = space();
    			button1 = element("button");
    			button1.textContent = "Delete";
    			t5 = space();
    			button2 = element("button");
    			button2.textContent = "DFA";
    			t7 = space();
    			if (if_block) if_block.c();
    			attr_dev(h2, "class", "shiny-text svelte-191atea");
    			add_location(h2, file$8, 290, 4, 6936);
    			attr_dev(button0, "class", "round-button svelte-191atea");
    			add_location(button0, file$8, 292, 5, 7007);
    			attr_dev(button1, "class", "round-button svelte-191atea");
    			add_location(button1, file$8, 293, 5, 7094);
    			attr_dev(button2, "class", "round-button dfa-button svelte-191atea");
    			toggle_class(button2, "active", /*isDFAActive*/ ctx[7]);
    			toggle_class(button2, "inactive", !/*isDFAActive*/ ctx[7]);
    			add_location(button2, file$8, 294, 5, 7181);
    			attr_dev(div, "class", "profile-info svelte-191atea");
    			add_location(div, file$8, 291, 4, 6975);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, h2, anchor);
    			append_dev(h2, t0);
    			insert_dev(target, t1, anchor);
    			insert_dev(target, div, anchor);
    			append_dev(div, button0);
    			append_dev(div, t3);
    			append_dev(div, button1);
    			append_dev(div, t5);
    			append_dev(div, button2);
    			append_dev(div, t7);
    			if (if_block) if_block.m(div, null);

    			if (!mounted) {
    				dispose = [
    					listen_dev(button0, "click", /*click_handler_2*/ ctx[30], false, false, false, false),
    					listen_dev(button1, "click", /*click_handler_3*/ ctx[31], false, false, false, false),
    					listen_dev(button2, "click", /*click_handler_4*/ ctx[32], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*name*/ 4) set_data_dev(t0, /*name*/ ctx[2]);

    			if (dirty[0] & /*isDFAActive*/ 128) {
    				toggle_class(button2, "active", /*isDFAActive*/ ctx[7]);
    			}

    			if (dirty[0] & /*isDFAActive*/ 128) {
    				toggle_class(button2, "inactive", !/*isDFAActive*/ ctx[7]);
    			}

    			if (/*qrCodeImageUrl*/ ctx[9]) {
    				if (if_block) {
    					if_block.p(ctx, dirty);
    				} else {
    					if_block = create_if_block_5$2(ctx);
    					if_block.c();
    					if_block.m(div, null);
    				}
    			} else if (if_block) {
    				if_block.d(1);
    				if_block = null;
    			}
    		},
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(h2);
    			if (detaching) detach_dev(t1);
    			if (detaching) detach_dev(div);
    			if (if_block) if_block.d();
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_4$3.name,
    		type: "if",
    		source: "(290:3) {#if targetId === id}",
    		ctx
    	});

    	return block;
    }

    // (303:5) {#if qrCodeImageUrl}
    function create_if_block_5$2(ctx) {
    	let img_1;
    	let img_1_src_value;

    	const block = {
    		c: function create() {
    			img_1 = element("img");
    			if (!src_url_equal(img_1.src, img_1_src_value = /*qrCodeImageUrl*/ ctx[9])) attr_dev(img_1, "src", img_1_src_value);
    			attr_dev(img_1, "alt", "QR Code");
    			add_location(img_1, file$8, 303, 7, 7417);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, img_1, anchor);
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*qrCodeImageUrl*/ 512 && !src_url_equal(img_1.src, img_1_src_value = /*qrCodeImageUrl*/ ctx[9])) {
    				attr_dev(img_1, "src", img_1_src_value);
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(img_1);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_5$2.name,
    		type: "if",
    		source: "(303:5) {#if qrCodeImageUrl}",
    		ctx
    	});

    	return block;
    }

    // (352:3) {:else}
    function create_else_block$2(ctx) {
    	let p;

    	const block = {
    		c: function create() {
    			p = element("p");
    			p.textContent = "didn't play yet";
    			add_location(p, file$8, 352, 4, 9007);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block$2.name,
    		type: "else",
    		source: "(352:3) {:else}",
    		ctx
    	});

    	return block;
    }

    // (341:3) {#if stats}
    function create_if_block_1$4(ctx) {
    	let p0;
    	let t0;
    	let t1_value = /*stats*/ ctx[6].played + "";
    	let t1;
    	let t2;
    	let p1;
    	let t3;
    	let t4_value = /*stats*/ ctx[6].won + "";
    	let t4;
    	let t5;
    	let t6;
    	let t7;
    	let p2;
    	let t8_value = /*stats*/ ctx[6].won * 100 / /*stats*/ ctx[6].played + "";
    	let t8;
    	let t9;
    	let t10;
    	let p3;
    	let t11;
    	let t12_value = /*stats*/ ctx[6].score + "";
    	let t12;
    	let if_block0 = /*stats*/ ctx[6].hf && create_if_block_3$3(ctx);
    	let if_block1 = /*stats*/ ctx[6].title && create_if_block_2$3(ctx);

    	const block = {
    		c: function create() {
    			p0 = element("p");
    			t0 = text("played: ");
    			t1 = text(t1_value);
    			t2 = space();
    			p1 = element("p");
    			t3 = text("won: ");
    			t4 = text(t4_value);
    			t5 = space();
    			if (if_block0) if_block0.c();
    			t6 = space();
    			if (if_block1) if_block1.c();
    			t7 = space();
    			p2 = element("p");
    			t8 = text(t8_value);
    			t9 = text("% victory");
    			t10 = space();
    			p3 = element("p");
    			t11 = text("score: ");
    			t12 = text(t12_value);
    			add_location(p0, file$8, 341, 4, 8709);
    			add_location(p1, file$8, 342, 4, 8747);
    			add_location(p2, file$8, 349, 4, 8905);
    			add_location(p3, file$8, 350, 4, 8960);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p0, anchor);
    			append_dev(p0, t0);
    			append_dev(p0, t1);
    			insert_dev(target, t2, anchor);
    			insert_dev(target, p1, anchor);
    			append_dev(p1, t3);
    			append_dev(p1, t4);
    			insert_dev(target, t5, anchor);
    			if (if_block0) if_block0.m(target, anchor);
    			insert_dev(target, t6, anchor);
    			if (if_block1) if_block1.m(target, anchor);
    			insert_dev(target, t7, anchor);
    			insert_dev(target, p2, anchor);
    			append_dev(p2, t8);
    			append_dev(p2, t9);
    			insert_dev(target, t10, anchor);
    			insert_dev(target, p3, anchor);
    			append_dev(p3, t11);
    			append_dev(p3, t12);
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*stats*/ 64 && t1_value !== (t1_value = /*stats*/ ctx[6].played + "")) set_data_dev(t1, t1_value);
    			if (dirty[0] & /*stats*/ 64 && t4_value !== (t4_value = /*stats*/ ctx[6].won + "")) set_data_dev(t4, t4_value);

    			if (/*stats*/ ctx[6].hf) {
    				if (if_block0) {
    					if_block0.p(ctx, dirty);
    				} else {
    					if_block0 = create_if_block_3$3(ctx);
    					if_block0.c();
    					if_block0.m(t6.parentNode, t6);
    				}
    			} else if (if_block0) {
    				if_block0.d(1);
    				if_block0 = null;
    			}

    			if (/*stats*/ ctx[6].title) {
    				if (if_block1) {
    					if_block1.p(ctx, dirty);
    				} else {
    					if_block1 = create_if_block_2$3(ctx);
    					if_block1.c();
    					if_block1.m(t7.parentNode, t7);
    				}
    			} else if (if_block1) {
    				if_block1.d(1);
    				if_block1 = null;
    			}

    			if (dirty[0] & /*stats*/ 64 && t8_value !== (t8_value = /*stats*/ ctx[6].won * 100 / /*stats*/ ctx[6].played + "")) set_data_dev(t8, t8_value);
    			if (dirty[0] & /*stats*/ 64 && t12_value !== (t12_value = /*stats*/ ctx[6].score + "")) set_data_dev(t12, t12_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p0);
    			if (detaching) detach_dev(t2);
    			if (detaching) detach_dev(p1);
    			if (detaching) detach_dev(t5);
    			if (if_block0) if_block0.d(detaching);
    			if (detaching) detach_dev(t6);
    			if (if_block1) if_block1.d(detaching);
    			if (detaching) detach_dev(t7);
    			if (detaching) detach_dev(p2);
    			if (detaching) detach_dev(t10);
    			if (detaching) detach_dev(p3);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_1$4.name,
    		type: "if",
    		source: "(341:3) {#if stats}",
    		ctx
    	});

    	return block;
    }

    // (344:4) {#if stats.hf}
    function create_if_block_3$3(ctx) {
    	let p;
    	let t0;
    	let t1_value = /*stats*/ ctx[6].hf + "";
    	let t1;

    	const block = {
    		c: function create() {
    			p = element("p");
    			t0 = text("hf: ");
    			t1 = text(t1_value);
    			add_location(p, file$8, 344, 5, 8799);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    			append_dev(p, t0);
    			append_dev(p, t1);
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*stats*/ 64 && t1_value !== (t1_value = /*stats*/ ctx[6].hf + "")) set_data_dev(t1, t1_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_3$3.name,
    		type: "if",
    		source: "(344:4) {#if stats.hf}",
    		ctx
    	});

    	return block;
    }

    // (347:4) {#if stats.title}
    function create_if_block_2$3(ctx) {
    	let p;
    	let t0;
    	let t1_value = /*stats*/ ctx[6].title + "";
    	let t1;

    	const block = {
    		c: function create() {
    			p = element("p");
    			t0 = text("hf: ");
    			t1 = text(t1_value);
    			add_location(p, file$8, 347, 5, 8862);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    			append_dev(p, t0);
    			append_dev(p, t1);
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*stats*/ 64 && t1_value !== (t1_value = /*stats*/ ctx[6].title + "")) set_data_dev(t1, t1_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_2$3.name,
    		type: "if",
    		source: "(347:4) {#if stats.title}",
    		ctx
    	});

    	return block;
    }

    // (362:4) {#if id42NameInputNotEmpty}
    function create_if_block$5(ctx) {
    	let div;
    	let each_value = /*searchRes*/ ctx[3];
    	validate_each_argument(each_value);
    	let each_blocks = [];

    	for (let i = 0; i < each_value.length; i += 1) {
    		each_blocks[i] = create_each_block$3(get_each_context$3(ctx, each_value, i));
    	}

    	const block = {
    		c: function create() {
    			div = element("div");

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				each_blocks[i].c();
    			}

    			attr_dev(div, "class", "popup svelte-191atea");
    			add_location(div, file$8, 362, 5, 9357);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div, anchor);

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				if (each_blocks[i]) {
    					each_blocks[i].m(div, null);
    				}
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*moveDisplayToTargetClient, searchRes*/ 65544) {
    				each_value = /*searchRes*/ ctx[3];
    				validate_each_argument(each_value);
    				let i;

    				for (i = 0; i < each_value.length; i += 1) {
    					const child_ctx = get_each_context$3(ctx, each_value, i);

    					if (each_blocks[i]) {
    						each_blocks[i].p(child_ctx, dirty);
    					} else {
    						each_blocks[i] = create_each_block$3(child_ctx);
    						each_blocks[i].c();
    						each_blocks[i].m(div, null);
    					}
    				}

    				for (; i < each_blocks.length; i += 1) {
    					each_blocks[i].d(1);
    				}

    				each_blocks.length = each_value.length;
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div);
    			destroy_each(each_blocks, detaching);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block$5.name,
    		type: "if",
    		source: "(362:4) {#if id42NameInputNotEmpty}",
    		ctx
    	});

    	return block;
    }

    // (364:6) {#each searchRes as client}
    function create_each_block$3(ctx) {
    	let button;
    	let t_value = /*client*/ ctx[49].name + "";
    	let t;
    	let mounted;
    	let dispose;

    	function click_handler_9() {
    		return /*click_handler_9*/ ctx[38](/*client*/ ctx[49]);
    	}

    	const block = {
    		c: function create() {
    			button = element("button");
    			t = text(t_value);
    			attr_dev(button, "class", "popup-button svelte-191atea");
    			add_location(button, file$8, 364, 7, 9418);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, button, anchor);
    			append_dev(button, t);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_9, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			if (dirty[0] & /*searchRes*/ 8 && t_value !== (t_value = /*client*/ ctx[49].name + "")) set_data_dev(t, t_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_each_block$3.name,
    		type: "each",
    		source: "(364:6) {#each searchRes as client}",
    		ctx
    	});

    	return block;
    }

    function create_fragment$8(ctx) {
    	let updatemodal;
    	let t0;
    	let deletemodal;
    	let t1;
    	let div4;
    	let main;
    	let div0;
    	let current_block_type_index;
    	let if_block0;
    	let t2;
    	let div1;
    	let h2;
    	let t4;
    	let t5;
    	let div3;
    	let label;
    	let t7;
    	let input;
    	let t8;
    	let div2;
    	let current;
    	let mounted;
    	let dispose;

    	updatemodal = new Update({
    			props: {
    				updatePop: /*updatePop*/ ctx[10],
    				id: /*id*/ ctx[12]
    			},
    			$$inline: true
    		});

    	updatemodal.$on("click", /*click_handler*/ ctx[27]);
    	updatemodal.$on("updated", /*updated_handler*/ ctx[28]);

    	deletemodal = new Delete({
    			props: { deletePop: /*deletePop*/ ctx[11] },
    			$$inline: true
    		});

    	deletemodal.$on("click", /*click_handler_1*/ ctx[29]);
    	const if_block_creators = [create_if_block_4$3, create_else_block_1$2];
    	const if_blocks = [];

    	function select_block_type(ctx, dirty) {
    		if (/*targetId*/ ctx[0] === /*id*/ ctx[12]) return 0;
    		return 1;
    	}

    	current_block_type_index = select_block_type(ctx);
    	if_block0 = if_blocks[current_block_type_index] = if_block_creators[current_block_type_index](ctx);

    	function select_block_type_1(ctx, dirty) {
    		if (/*stats*/ ctx[6]) return create_if_block_1$4;
    		return create_else_block$2;
    	}

    	let current_block_type = select_block_type_1(ctx);
    	let if_block1 = current_block_type(ctx);
    	let if_block2 = /*id42NameInputNotEmpty*/ ctx[1] && create_if_block$5(ctx);

    	const block = {
    		c: function create() {
    			create_component(updatemodal.$$.fragment);
    			t0 = space();
    			create_component(deletemodal.$$.fragment);
    			t1 = space();
    			div4 = element("div");
    			main = element("main");
    			div0 = element("div");
    			if_block0.c();
    			t2 = space();
    			div1 = element("div");
    			h2 = element("h2");
    			h2.textContent = "Stats";
    			t4 = space();
    			if_block1.c();
    			t5 = space();
    			div3 = element("div");
    			label = element("label");
    			label.textContent = "search by Name:";
    			t7 = space();
    			input = element("input");
    			t8 = space();
    			div2 = element("div");
    			if (if_block2) if_block2.c();
    			attr_dev(div0, "class", "profile-container svelte-191atea");
    			add_location(div0, file$8, 288, 2, 6875);
    			add_location(h2, file$8, 339, 3, 8675);
    			add_location(div1, file$8, 338, 2, 8666);
    			attr_dev(label, "for", "id42-name-input");
    			add_location(label, file$8, 357, 3, 9145);
    			attr_dev(input, "type", "text");
    			attr_dev(input, "id", "id42-name-input");
    			add_location(input, file$8, 358, 3, 9201);
    			attr_dev(div2, "class", "popup_container svelte-191atea");
    			add_location(div2, file$8, 360, 3, 9290);
    			add_location(div3, file$8, 356, 2, 9136);
    			attr_dev(main, "class", "container svelte-191atea");
    			add_location(main, file$8, 286, 1, 6762);
    			attr_dev(div4, "class", "main_body");
    			add_location(div4, file$8, 284, 0, 6736);
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			mount_component(updatemodal, target, anchor);
    			insert_dev(target, t0, anchor);
    			mount_component(deletemodal, target, anchor);
    			insert_dev(target, t1, anchor);
    			insert_dev(target, div4, anchor);
    			append_dev(div4, main);
    			append_dev(main, div0);
    			if_blocks[current_block_type_index].m(div0, null);
    			append_dev(main, t2);
    			append_dev(main, div1);
    			append_dev(div1, h2);
    			append_dev(div1, t4);
    			if_block1.m(div1, null);
    			append_dev(main, t5);
    			append_dev(main, div3);
    			append_dev(div3, label);
    			append_dev(div3, t7);
    			append_dev(div3, input);
    			append_dev(div3, t8);
    			append_dev(div3, div2);
    			if (if_block2) if_block2.m(div2, null);
    			current = true;

    			if (!mounted) {
    				dispose = listen_dev(input, "input", /*input_handler*/ ctx[37], false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(ctx, dirty) {
    			const updatemodal_changes = {};
    			if (dirty[0] & /*updatePop*/ 1024) updatemodal_changes.updatePop = /*updatePop*/ ctx[10];
    			updatemodal.$set(updatemodal_changes);
    			const deletemodal_changes = {};
    			if (dirty[0] & /*deletePop*/ 2048) deletemodal_changes.deletePop = /*deletePop*/ ctx[11];
    			deletemodal.$set(deletemodal_changes);
    			let previous_block_index = current_block_type_index;
    			current_block_type_index = select_block_type(ctx);

    			if (current_block_type_index === previous_block_index) {
    				if_blocks[current_block_type_index].p(ctx, dirty);
    			} else {
    				group_outros();

    				transition_out(if_blocks[previous_block_index], 1, 1, () => {
    					if_blocks[previous_block_index] = null;
    				});

    				check_outros();
    				if_block0 = if_blocks[current_block_type_index];

    				if (!if_block0) {
    					if_block0 = if_blocks[current_block_type_index] = if_block_creators[current_block_type_index](ctx);
    					if_block0.c();
    				} else {
    					if_block0.p(ctx, dirty);
    				}

    				transition_in(if_block0, 1);
    				if_block0.m(div0, null);
    			}

    			if (current_block_type === (current_block_type = select_block_type_1(ctx)) && if_block1) {
    				if_block1.p(ctx, dirty);
    			} else {
    				if_block1.d(1);
    				if_block1 = current_block_type(ctx);

    				if (if_block1) {
    					if_block1.c();
    					if_block1.m(div1, null);
    				}
    			}

    			if (/*id42NameInputNotEmpty*/ ctx[1]) {
    				if (if_block2) {
    					if_block2.p(ctx, dirty);
    				} else {
    					if_block2 = create_if_block$5(ctx);
    					if_block2.c();
    					if_block2.m(div2, null);
    				}
    			} else if (if_block2) {
    				if_block2.d(1);
    				if_block2 = null;
    			}
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(updatemodal.$$.fragment, local);
    			transition_in(deletemodal.$$.fragment, local);
    			transition_in(if_block0);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(updatemodal.$$.fragment, local);
    			transition_out(deletemodal.$$.fragment, local);
    			transition_out(if_block0);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(updatemodal, detaching);
    			if (detaching) detach_dev(t0);
    			destroy_component(deletemodal, detaching);
    			if (detaching) detach_dev(t1);
    			if (detaching) detach_dev(div4);
    			if_blocks[current_block_type_index].d();
    			if_block1.d();
    			if (if_block2) if_block2.d();
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$8.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$8($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Dashboard', slots, []);
    	const dispatch = createEventDispatcher();
    	let { data } = $$props;
    	let { targetId } = $$props;

    	// display boolean
    	let id42NameInputNotEmpty = false;

    	// Personnal page
    	let id42 = data.id42;

    	let id = data.id;
    	let name = data.name;
    	let img = data.img;
    	let Dfa = data.Dfa;
    	let searchRes = [];

    	// Target to inspect
    	// let targetId = data.id;
    	let targetName = name;

    	let targetImg = img;

    	// stats are always target ones
    	let stats = {};

    	//HF Titles
    	let HF = ["pas du tout", "un peu", "beaucoup", "passionnément", "à la folie"];

    	let title = [
    		"Straitght outta bronze",
    		"Golden pad",
    		"Diamonds Are Forever",
    		"Big Brother",
    		"Daddy"
    	];

    	let isDFAActive = Dfa;
    	let blocked = false;
    	let qrCodeImageUrl = "";

    	function toggleBlockState() {
    		$$invalidate(8, blocked = !blocked);
    	}

    	onMount(async () => {
    		await fetchTargetData();
    		await getTargetStats();
    	});

    	async function fetchData() {
    		try {
    			const response = await fetch(`http://${hostname}:3000/dashboard/${id42}`);
    			$$invalidate(26, data = await response.json());
    			$$invalidate(2, name = data.name);
    			img = data.img;
    			returnBackHome();
    			return data;
    		} catch(error) {
    			console.error(error);
    		}
    	}

    	async function fetchTargetData() {
    		try {
    			const response = await fetch(`http://${hostname}:3000/dashboard/42/${targetId}`);
    			$$invalidate(26, data = await response.json());
    			$$invalidate(4, targetName = data.name);
    			$$invalidate(5, targetImg = data.img);

    			// returnBackHome();
    			return data;
    		} catch(error) {
    			console.error(error);
    		}
    	}

    	async function toggleDFAState() {
    		$$invalidate(7, isDFAActive = !isDFAActive);

    		// Send API request to update DFA status
    		try {
    			const response = await axios$1.post(`http://${hostname}:3000/auth/2fa/${id}`, { isDFAActive });
    			console.log('DFA status updated in the database.');
    			$$invalidate(9, qrCodeImageUrl = response.data.qrCodeImageUrl);
    		} catch(error) {
    			console.error('Failed to update DFA status:', error);
    		}
    	}

    	async function getSpecifiedClients() {
    		const retName = document.getElementById('id42-name-input').value;
    		$$invalidate(1, id42NameInputNotEmpty = retName.trim() !== '');

    		if (id42NameInputNotEmpty) {
    			try {
    				const response = await fetch(`http://${hostname}:3000/dashboard/name/${retName}`);
    				$$invalidate(3, searchRes = await response.json());
    			} catch(error) {
    				console.error(error);
    			}
    		} else $$invalidate(3, searchRes = []);
    	}

    	async function getTargetStats() {
    		try {
    			const response = await fetch(`http://${hostname}:3000/dashboard/stats/${targetId}`);
    			if (response) $$invalidate(6, stats = await response.json()); else $$invalidate(6, stats = null);
    		} catch(error) {
    			console.error(error);
    		}
    	}

    	function moveDisplayToTargetClient(client) {
    		$$invalidate(0, targetId = client.id);
    		$$invalidate(4, targetName = client.name);
    		if (client.img === "undefined") $$invalidate(5, targetImg = "img/il_794xN.3892173164_egqv.avif"); else $$invalidate(5, targetImg = client.img);
    		getTargetStats();
    		document.getElementById('id42-name-input').value = "";
    		$$invalidate(3, searchRes = []);
    		$$invalidate(1, id42NameInputNotEmpty = null);
    	}

    	function returnBackHome() {
    		$$invalidate(0, targetId = id);
    		$$invalidate(4, targetName = name);
    		$$invalidate(5, targetImg = img);
    		getTargetStats();
    		document.getElementById('id42-name-input').value = "";
    		$$invalidate(3, searchRes = []);
    		$$invalidate(1, id42NameInputNotEmpty = null);
    	}

    	//---------------------------------------------------------------------------//
    	const addFriend = async newFriendId => {
    		await fetch(`http://${hostname}:3000/chat/addFriend`, {
    			method: 'POST',
    			headers: { 'Content-Type': 'application/json' },
    			body: JSON.stringify({ newFriendId, iddata: data.id })
    		});
    	}; // if (response.ok) {
    	// 	console.log('Joined room:', room.name);
    	// } else {
    	// 	console.error('Failed to join room:', room.name);

    	// }
    	//---------------------------------------------------------------------------//
    	const blockUser = async blockedId => {
    		const response = await fetch(`http://${hostname}:3000/chat/blockUser`, {
    			method: 'POST',
    			headers: { 'Content-Type': 'application/json' },
    			body: JSON.stringify({ blockedId, iddata: data.id })
    		});

    		if (response.ok) {
    			console.log('User blocked');
    		} else {
    			console.error('Failed to block user');
    		}
    	};

    	//---------------------------------------------------------------------------//
    	const unblockUser = async unblockedId => {
    		const response = await fetch(`http://${hostname}:3000/chat/unblockUser`, {
    			method: 'POST',
    			headers: { 'Content-Type': 'application/json' },
    			body: JSON.stringify({ unblockedId, iddata: data.id })
    		});

    		if (response.ok) {
    			console.log('User unblocked');
    		} else {
    			console.error('Failed to unblock user');
    		}
    	};

    	//---------------------------------------------------------------------------//
    	const MP = async newFriendId => {
    		console.log('here');

    		const response = await fetch(`http://${hostname}:3000/chat/sendMsg`, {
    			method: 'POST',
    			headers: { 'Content-Type': 'application/json' },
    			body: JSON.stringify({ newFriendId, iddata: data.id })
    		});

    		if (response.ok) {
    			console.log('Joined room:', room.name);
    		} else {
    			console.error('Failed to join room:', room.name);
    		}
    	};

    	//---------------------------------------------------------------------------//
    	const play = async newFriend => {
    		
    	}; // const response = await fetch(`http://${hostname}:3000/chat/addFriend`, {
    	// 	method: 'POST',
    	// 	headers: {
    	// 		'Content-Type': 'application/json'

    	// 	},
    	// 	body: JSON.stringify({
    	// 		newFriendId: newFriend.id,
    	// 		iddata: data.id
    	// 	})
    	// });
    	// if (response.ok) {
    	// 	console.log('Joined room:', room.name);
    	// } else {
    	// 	console.error('Failed to join room:', room.name);
    	// }
    	//---------------------------------------------------------------------------//
    	async function profileUpdate() {
    		let client = await fetchData();
    		dispatch("updateProfile", client);
    	}

    	let updatePop = false;

    	function toggleUpdatePopup() {
    		$$invalidate(10, updatePop = !updatePop);
    	}

    	let deletePop = false;

    	function toggleDeletePopup() {
    		$$invalidate(11, deletePop = !deletePop);
    	}

    	function sendInvitation() {
    		socket.chat.emit('inviteToPlay', { player_id: data.id, opponent_id });
    	} //appeler une foncion de creation de la game + redirection vers la game
    	//mais je sais pas faire

    	$$self.$$.on_mount.push(function () {
    		if (data === undefined && !('data' in $$props || $$self.$$.bound[$$self.$$.props['data']])) {
    			console_1$6.warn("<Dashboard> was created without expected prop 'data'");
    		}

    		if (targetId === undefined && !('targetId' in $$props || $$self.$$.bound[$$self.$$.props['targetId']])) {
    			console_1$6.warn("<Dashboard> was created without expected prop 'targetId'");
    		}
    	});

    	const writable_props = ['data', 'targetId'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console_1$6.warn(`<Dashboard> was created with unknown prop '${key}'`);
    	});

    	const click_handler = () => toggleUpdatePopup();
    	const updated_handler = () => profileUpdate();
    	const click_handler_1 = () => toggleDeletePopup();
    	const click_handler_2 = () => toggleUpdatePopup();
    	const click_handler_3 = () => toggleDeletePopup();
    	const click_handler_4 = () => toggleDFAState();
    	const click_handler_5 = () => returnBackHome();
    	const click_handler_6 = () => addFriend(targetId);

    	const click_handler_7 = () => {
    		if (blocked) {
    			unblockUser(targetId);
    		} else {
    			blockUser(targetId);
    		}

    		toggleBlockState();
    	};

    	const click_handler_8 = () => MP(targetId);
    	const input_handler = () => getSpecifiedClients();
    	const click_handler_9 = client => moveDisplayToTargetClient(client);

    	$$self.$$set = $$props => {
    		if ('data' in $$props) $$invalidate(26, data = $$props.data);
    		if ('targetId' in $$props) $$invalidate(0, targetId = $$props.targetId);
    	};

    	$$self.$capture_state = () => ({
    		onMount,
    		createEventDispatcher,
    		UpdateModal: Update,
    		DeleteModal: Delete,
    		hostname,
    		axios: axios$1,
    		ConnectStatus,
    		dispatch,
    		data,
    		targetId,
    		id42NameInputNotEmpty,
    		id42,
    		id,
    		name,
    		img,
    		Dfa,
    		searchRes,
    		targetName,
    		targetImg,
    		stats,
    		HF,
    		title,
    		isDFAActive,
    		blocked,
    		qrCodeImageUrl,
    		toggleBlockState,
    		fetchData,
    		fetchTargetData,
    		toggleDFAState,
    		getSpecifiedClients,
    		getTargetStats,
    		moveDisplayToTargetClient,
    		returnBackHome,
    		addFriend,
    		blockUser,
    		unblockUser,
    		MP,
    		play,
    		profileUpdate,
    		updatePop,
    		toggleUpdatePopup,
    		deletePop,
    		toggleDeletePopup,
    		sendInvitation
    	});

    	$$self.$inject_state = $$props => {
    		if ('data' in $$props) $$invalidate(26, data = $$props.data);
    		if ('targetId' in $$props) $$invalidate(0, targetId = $$props.targetId);
    		if ('id42NameInputNotEmpty' in $$props) $$invalidate(1, id42NameInputNotEmpty = $$props.id42NameInputNotEmpty);
    		if ('id42' in $$props) id42 = $$props.id42;
    		if ('id' in $$props) $$invalidate(12, id = $$props.id);
    		if ('name' in $$props) $$invalidate(2, name = $$props.name);
    		if ('img' in $$props) img = $$props.img;
    		if ('Dfa' in $$props) Dfa = $$props.Dfa;
    		if ('searchRes' in $$props) $$invalidate(3, searchRes = $$props.searchRes);
    		if ('targetName' in $$props) $$invalidate(4, targetName = $$props.targetName);
    		if ('targetImg' in $$props) $$invalidate(5, targetImg = $$props.targetImg);
    		if ('stats' in $$props) $$invalidate(6, stats = $$props.stats);
    		if ('HF' in $$props) HF = $$props.HF;
    		if ('title' in $$props) title = $$props.title;
    		if ('isDFAActive' in $$props) $$invalidate(7, isDFAActive = $$props.isDFAActive);
    		if ('blocked' in $$props) $$invalidate(8, blocked = $$props.blocked);
    		if ('qrCodeImageUrl' in $$props) $$invalidate(9, qrCodeImageUrl = $$props.qrCodeImageUrl);
    		if ('updatePop' in $$props) $$invalidate(10, updatePop = $$props.updatePop);
    		if ('deletePop' in $$props) $$invalidate(11, deletePop = $$props.deletePop);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [
    		targetId,
    		id42NameInputNotEmpty,
    		name,
    		searchRes,
    		targetName,
    		targetImg,
    		stats,
    		isDFAActive,
    		blocked,
    		qrCodeImageUrl,
    		updatePop,
    		deletePop,
    		id,
    		toggleBlockState,
    		toggleDFAState,
    		getSpecifiedClients,
    		moveDisplayToTargetClient,
    		returnBackHome,
    		addFriend,
    		blockUser,
    		unblockUser,
    		MP,
    		profileUpdate,
    		toggleUpdatePopup,
    		toggleDeletePopup,
    		sendInvitation,
    		data,
    		click_handler,
    		updated_handler,
    		click_handler_1,
    		click_handler_2,
    		click_handler_3,
    		click_handler_4,
    		click_handler_5,
    		click_handler_6,
    		click_handler_7,
    		click_handler_8,
    		input_handler,
    		click_handler_9
    	];
    }

    class Dashboard extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$8, create_fragment$8, safe_not_equal, { data: 26, targetId: 0 }, null, [-1, -1]);

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Dashboard",
    			options,
    			id: create_fragment$8.name
    		});
    	}

    	get data() {
    		throw new Error("<Dashboard>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set data(value) {
    		throw new Error("<Dashboard>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	get targetId() {
    		throw new Error("<Dashboard>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set targetId(value) {
    		throw new Error("<Dashboard>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/shared/Invitation.svelte generated by Svelte v3.59.1 */

    const file$7 = "src/shared/Invitation.svelte";

    function create_fragment$7(ctx) {
    	let button;
    	let mounted;
    	let dispose;

    	const block = {
    		c: function create() {
    			button = element("button");
    			button.textContent = "Defier";
    			add_location(button, file$7, 14, 0, 302);
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, button, anchor);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", /*sendInvitation*/ ctx[0], false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: noop$1,
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$7.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$7($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Invitation', slots, []);
    	let { socket } = $$props;
    	let { opponent_id } = $$props;
    	let { data } = $$props;

    	function sendInvitation() {
    		socket.chat.emit('inviteToPlay', { player_id: data.id, opponent_id });
    	} //appeler une foncion de creation de la game + redirection vers la game
    	//mais je sais pas faire

    	$$self.$$.on_mount.push(function () {
    		if (socket === undefined && !('socket' in $$props || $$self.$$.bound[$$self.$$.props['socket']])) {
    			console.warn("<Invitation> was created without expected prop 'socket'");
    		}

    		if (opponent_id === undefined && !('opponent_id' in $$props || $$self.$$.bound[$$self.$$.props['opponent_id']])) {
    			console.warn("<Invitation> was created without expected prop 'opponent_id'");
    		}

    		if (data === undefined && !('data' in $$props || $$self.$$.bound[$$self.$$.props['data']])) {
    			console.warn("<Invitation> was created without expected prop 'data'");
    		}
    	});

    	const writable_props = ['socket', 'opponent_id', 'data'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console.warn(`<Invitation> was created with unknown prop '${key}'`);
    	});

    	$$self.$$set = $$props => {
    		if ('socket' in $$props) $$invalidate(1, socket = $$props.socket);
    		if ('opponent_id' in $$props) $$invalidate(2, opponent_id = $$props.opponent_id);
    		if ('data' in $$props) $$invalidate(3, data = $$props.data);
    	};

    	$$self.$capture_state = () => ({
    		socket,
    		opponent_id,
    		data,
    		sendInvitation
    	});

    	$$self.$inject_state = $$props => {
    		if ('socket' in $$props) $$invalidate(1, socket = $$props.socket);
    		if ('opponent_id' in $$props) $$invalidate(2, opponent_id = $$props.opponent_id);
    		if ('data' in $$props) $$invalidate(3, data = $$props.data);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [sendInvitation, socket, opponent_id, data];
    }

    class Invitation extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$7, create_fragment$7, safe_not_equal, { socket: 1, opponent_id: 2, data: 3 });

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Invitation",
    			options,
    			id: create_fragment$7.name
    		});
    	}

    	get socket() {
    		throw new Error("<Invitation>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set socket(value) {
    		throw new Error("<Invitation>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	get opponent_id() {
    		throw new Error("<Invitation>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set opponent_id(value) {
    		throw new Error("<Invitation>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	get data() {
    		throw new Error("<Invitation>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set data(value) {
    		throw new Error("<Invitation>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/component/chat/leave_verif.svelte generated by Svelte v3.59.1 */

    const { Error: Error_1$2, console: console_1$5 } = globals;
    const file$6 = "src/component/chat/leave_verif.svelte";

    // (34:0) {#if verifTab}
    function create_if_block$4(ctx) {
    	let div1;
    	let div0;
    	let h1;
    	let t1;
    	let button0;
    	let t3;
    	let button1;
    	let mounted;
    	let dispose;

    	const block = {
    		c: function create() {
    			div1 = element("div");
    			div0 = element("div");
    			h1 = element("h1");
    			h1.textContent = "Are you sure ?";
    			t1 = space();
    			button0 = element("button");
    			button0.textContent = "yes";
    			t3 = space();
    			button1 = element("button");
    			button1.textContent = "no";
    			add_location(h1, file$6, 36, 3, 695);
    			add_location(button0, file$6, 37, 3, 722);
    			add_location(button1, file$6, 38, 3, 770);
    			attr_dev(div0, "class", "modal svelte-1ilhx9i");
    			add_location(div0, file$6, 35, 2, 672);
    			attr_dev(div1, "class", "backdrop svelte-1ilhx9i");
    			add_location(div1, file$6, 34, 1, 621);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div1, anchor);
    			append_dev(div1, div0);
    			append_dev(div0, h1);
    			append_dev(div0, t1);
    			append_dev(div0, button0);
    			append_dev(div0, t3);
    			append_dev(div0, button1);

    			if (!mounted) {
    				dispose = [
    					listen_dev(button0, "click", /*click_handler_2*/ ctx[7], false, false, false, false),
    					listen_dev(button1, "click", /*click_handler_1*/ ctx[6], false, false, false, false),
    					listen_dev(div1, "click", self$1(/*click_handler*/ ctx[4]), false, false, false, false),
    					listen_dev(div1, "keypress", /*keypress_handler*/ ctx[5], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div1);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block$4.name,
    		type: "if",
    		source: "(34:0) {#if verifTab}",
    		ctx
    	});

    	return block;
    }

    function create_fragment$6(ctx) {
    	let if_block_anchor;
    	let if_block = /*verifTab*/ ctx[0] && create_if_block$4(ctx);

    	const block = {
    		c: function create() {
    			if (if_block) if_block.c();
    			if_block_anchor = empty$1();
    		},
    		l: function claim(nodes) {
    			throw new Error_1$2("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			if (if_block) if_block.m(target, anchor);
    			insert_dev(target, if_block_anchor, anchor);
    		},
    		p: function update(ctx, [dirty]) {
    			if (/*verifTab*/ ctx[0]) {
    				if (if_block) {
    					if_block.p(ctx, dirty);
    				} else {
    					if_block = create_if_block$4(ctx);
    					if_block.c();
    					if_block.m(if_block_anchor.parentNode, if_block_anchor);
    				}
    			} else if (if_block) {
    				if_block.d(1);
    				if_block = null;
    			}
    		},
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (if_block) if_block.d(detaching);
    			if (detaching) detach_dev(if_block_anchor);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$6.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$6($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Leave_verif', slots, []);
    	const dispatch = createEventDispatcher();
    	let { id } = $$props;
    	let { roomId } = $$props;
    	let { verifTab } = $$props;

    	async function leave() {
    		try {
    			const response = await fetch(`http://${hostname}:3000/rooms/kick/${roomId}/${id}`, { method: 'POST' });

    			if (response.ok) console.log('client left'); else {
    				const errorText = await response.text();
    				throw new Error(errorText);
    			}
    		} catch(error) {
    			throw new Error(error.message);
    		}

    		dispatch('leaving');
    	}

    	$$self.$$.on_mount.push(function () {
    		if (id === undefined && !('id' in $$props || $$self.$$.bound[$$self.$$.props['id']])) {
    			console_1$5.warn("<Leave_verif> was created without expected prop 'id'");
    		}

    		if (roomId === undefined && !('roomId' in $$props || $$self.$$.bound[$$self.$$.props['roomId']])) {
    			console_1$5.warn("<Leave_verif> was created without expected prop 'roomId'");
    		}

    		if (verifTab === undefined && !('verifTab' in $$props || $$self.$$.bound[$$self.$$.props['verifTab']])) {
    			console_1$5.warn("<Leave_verif> was created without expected prop 'verifTab'");
    		}
    	});

    	const writable_props = ['id', 'roomId', 'verifTab'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console_1$5.warn(`<Leave_verif> was created with unknown prop '${key}'`);
    	});

    	function click_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	function keypress_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	function click_handler_1(event) {
    		bubble.call(this, $$self, event);
    	}

    	const click_handler_2 = () => leave();

    	$$self.$$set = $$props => {
    		if ('id' in $$props) $$invalidate(2, id = $$props.id);
    		if ('roomId' in $$props) $$invalidate(3, roomId = $$props.roomId);
    		if ('verifTab' in $$props) $$invalidate(0, verifTab = $$props.verifTab);
    	};

    	$$self.$capture_state = () => ({
    		hostname,
    		createEventDispatcher,
    		dispatch,
    		id,
    		roomId,
    		verifTab,
    		leave
    	});

    	$$self.$inject_state = $$props => {
    		if ('id' in $$props) $$invalidate(2, id = $$props.id);
    		if ('roomId' in $$props) $$invalidate(3, roomId = $$props.roomId);
    		if ('verifTab' in $$props) $$invalidate(0, verifTab = $$props.verifTab);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [
    		verifTab,
    		leave,
    		id,
    		roomId,
    		click_handler,
    		keypress_handler,
    		click_handler_1,
    		click_handler_2
    	];
    }

    class Leave_verif extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$6, create_fragment$6, safe_not_equal, { id: 2, roomId: 3, verifTab: 0 });

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Leave_verif",
    			options,
    			id: create_fragment$6.name
    		});
    	}

    	get id() {
    		throw new Error_1$2("<Leave_verif>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set id(value) {
    		throw new Error_1$2("<Leave_verif>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	get roomId() {
    		throw new Error_1$2("<Leave_verif>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set roomId(value) {
    		throw new Error_1$2("<Leave_verif>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	get verifTab() {
    		throw new Error_1$2("<Leave_verif>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set verifTab(value) {
    		throw new Error_1$2("<Leave_verif>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/component/chat/Chat.svelte generated by Svelte v3.59.1 */

    const { console: console_1$4 } = globals;
    const file$5 = "src/component/chat/Chat.svelte";

    function get_each_context$2(ctx, list, i) {
    	const child_ctx = ctx.slice();
    	child_ctx[27] = list[i];
    	return child_ctx;
    }

    function get_each_context_1$2(ctx, list, i) {
    	const child_ctx = ctx.slice();
    	child_ctx[30] = list[i];
    	return child_ctx;
    }

    // (1:0) <script>  import { io }
    function create_catch_block$3(ctx) {
    	const block = { c: noop$1, m: noop$1, p: noop$1, d: noop$1 };

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_catch_block$3.name,
    		type: "catch",
    		source: "(1:0) <script>  import { io }",
    		ctx
    	});

    	return block;
    }

    // (161:2) {:then}
    function create_then_block$3(ctx) {
    	let ul;
    	let each_blocks = [];
    	let each_1_lookup = new Map();
    	let each_value_1 = /*$rooms*/ ctx[6];
    	validate_each_argument(each_value_1);
    	const get_key = ctx => /*room*/ ctx[30].roomId;
    	validate_each_keys(ctx, each_value_1, get_each_context_1$2, get_key);

    	for (let i = 0; i < each_value_1.length; i += 1) {
    		let child_ctx = get_each_context_1$2(ctx, each_value_1, i);
    		let key = get_key(child_ctx);
    		each_1_lookup.set(key, each_blocks[i] = create_each_block_1$2(key, child_ctx));
    	}

    	let each_1_else = null;

    	if (!each_value_1.length) {
    		each_1_else = create_else_block_2$1(ctx);
    	}

    	const block = {
    		c: function create() {
    			ul = element("ul");

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				each_blocks[i].c();
    			}

    			if (each_1_else) {
    				each_1_else.c();
    			}

    			add_location(ul, file$5, 161, 2, 3858);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, ul, anchor);

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				if (each_blocks[i]) {
    					each_blocks[i].m(ul, null);
    				}
    			}

    			if (each_1_else) {
    				each_1_else.m(ul, null);
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*$rooms, selected_room_id, changeSelectedId, leaveRoom*/ 1218) {
    				each_value_1 = /*$rooms*/ ctx[6];
    				validate_each_argument(each_value_1);
    				validate_each_keys(ctx, each_value_1, get_each_context_1$2, get_key);
    				each_blocks = update_keyed_each(each_blocks, dirty, get_key, 1, ctx, each_value_1, each_1_lookup, ul, destroy_block, create_each_block_1$2, null, get_each_context_1$2);

    				if (!each_value_1.length && each_1_else) {
    					each_1_else.p(ctx, dirty);
    				} else if (!each_value_1.length) {
    					each_1_else = create_else_block_2$1(ctx);
    					each_1_else.c();
    					each_1_else.m(ul, null);
    				} else if (each_1_else) {
    					each_1_else.d(1);
    					each_1_else = null;
    				}
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(ul);

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				each_blocks[i].d();
    			}

    			if (each_1_else) each_1_else.d();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_then_block$3.name,
    		type: "then",
    		source: "(161:2) {:then}",
    		ctx
    	});

    	return block;
    }

    // (171:3) {:else}
    function create_else_block_2$1(ctx) {
    	let p;

    	const block = {
    		c: function create() {
    			p = element("p");
    			p.textContent = "you don't have friends";
    			add_location(p, file$5, 171, 3, 4298);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block_2$1.name,
    		type: "else",
    		source: "(171:3) {:else}",
    		ctx
    	});

    	return block;
    }

    // (166:5) {#if room.secu !== 3}
    function create_if_block_1$3(ctx) {
    	let button;
    	let mounted;
    	let dispose;

    	function click_handler_1() {
    		return /*click_handler_1*/ ctx[16](/*room*/ ctx[30]);
    	}

    	const block = {
    		c: function create() {
    			button = element("button");
    			button.textContent = "leave";
    			set_style(button, "float", "right");
    			add_location(button, file$5, 166, 6, 4094);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, button, anchor);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_1, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_1$3.name,
    		type: "if",
    		source: "(166:5) {#if room.secu !== 3}",
    		ctx
    	});

    	return block;
    }

    // (163:3) {#each $rooms as room (room.roomId)}
    function create_each_block_1$2(key_1, ctx) {
    	let li;
    	let t0_value = /*room*/ ctx[30].roomName + "";
    	let t0;
    	let t1;
    	let t2;
    	let div;
    	let t3_value = /*room*/ ctx[30].newMsgCount + "";
    	let t3;
    	let t4;
    	let mounted;
    	let dispose;
    	let if_block = /*room*/ ctx[30].secu !== 3 && create_if_block_1$3(ctx);

    	function click_handler_2() {
    		return /*click_handler_2*/ ctx[17](/*room*/ ctx[30]);
    	}

    	const block = {
    		key: key_1,
    		first: null,
    		c: function create() {
    			li = element("li");
    			t0 = text(t0_value);
    			t1 = space();
    			if (if_block) if_block.c();
    			t2 = space();
    			div = element("div");
    			t3 = text(t3_value);
    			t4 = space();
    			attr_dev(div, "class", "alertBox svelte-13wjb18");
    			toggle_class(div, "alertOn", /*room*/ ctx[30].newMsgCount !== 0);
    			add_location(div, file$5, 168, 5, 4188);
    			attr_dev(li, "class", "one_room svelte-13wjb18");
    			toggle_class(li, "activeroom", /*room*/ ctx[30].roomId === /*selected_room_id*/ ctx[1]);
    			add_location(li, file$5, 163, 4, 3907);
    			this.first = li;
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, li, anchor);
    			append_dev(li, t0);
    			append_dev(li, t1);
    			if (if_block) if_block.m(li, null);
    			append_dev(li, t2);
    			append_dev(li, div);
    			append_dev(div, t3);
    			append_dev(li, t4);

    			if (!mounted) {
    				dispose = [
    					listen_dev(li, "click", click_handler_2, false, false, false, false),
    					listen_dev(li, "keypress", /*keypress_handler*/ ctx[13], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			if (dirty[0] & /*$rooms*/ 64 && t0_value !== (t0_value = /*room*/ ctx[30].roomName + "")) set_data_dev(t0, t0_value);

    			if (/*room*/ ctx[30].secu !== 3) {
    				if (if_block) {
    					if_block.p(ctx, dirty);
    				} else {
    					if_block = create_if_block_1$3(ctx);
    					if_block.c();
    					if_block.m(li, t2);
    				}
    			} else if (if_block) {
    				if_block.d(1);
    				if_block = null;
    			}

    			if (dirty[0] & /*$rooms*/ 64 && t3_value !== (t3_value = /*room*/ ctx[30].newMsgCount + "")) set_data_dev(t3, t3_value);

    			if (dirty[0] & /*$rooms*/ 64) {
    				toggle_class(div, "alertOn", /*room*/ ctx[30].newMsgCount !== 0);
    			}

    			if (dirty[0] & /*$rooms, selected_room_id*/ 66) {
    				toggle_class(li, "activeroom", /*room*/ ctx[30].roomId === /*selected_room_id*/ ctx[1]);
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(li);
    			if (if_block) if_block.d();
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_each_block_1$2.name,
    		type: "each",
    		source: "(163:3) {#each $rooms as room (room.roomId)}",
    		ctx
    	});

    	return block;
    }

    // (159:24)     <center><p>Loading...</p></center>   {:then}
    function create_pending_block$3(ctx) {
    	let center;
    	let p;

    	const block = {
    		c: function create() {
    			center = element("center");
    			p = element("p");
    			p.textContent = "Loading...";
    			add_location(p, file$5, 159, 11, 3819);
    			add_location(center, file$5, 159, 3, 3811);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, center, anchor);
    			append_dev(center, p);
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(center);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_pending_block$3.name,
    		type: "pending",
    		source: "(159:24)     <center><p>Loading...</p></center>   {:then}",
    		ctx
    	});

    	return block;
    }

    // (183:3) {:else}
    function create_else_block$1(ctx) {
    	let if_block_anchor;

    	function select_block_type(ctx, dirty) {
    		if (/*selected_room_id*/ ctx[1] != -1) return create_if_block$3;
    		return create_else_block_1$1;
    	}

    	let current_block_type = select_block_type(ctx);
    	let if_block = current_block_type(ctx);

    	const block = {
    		c: function create() {
    			if_block.c();
    			if_block_anchor = empty$1();
    		},
    		m: function mount(target, anchor) {
    			if_block.m(target, anchor);
    			insert_dev(target, if_block_anchor, anchor);
    		},
    		p: function update(ctx, dirty) {
    			if (current_block_type !== (current_block_type = select_block_type(ctx))) {
    				if_block.d(1);
    				if_block = current_block_type(ctx);

    				if (if_block) {
    					if_block.c();
    					if_block.m(if_block_anchor.parentNode, if_block_anchor);
    				}
    			}
    		},
    		d: function destroy(detaching) {
    			if_block.d(detaching);
    			if (detaching) detach_dev(if_block_anchor);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block$1.name,
    		type: "else",
    		source: "(183:3) {:else}",
    		ctx
    	});

    	return block;
    }

    // (186:4) {:else}
    function create_else_block_1$1(ctx) {
    	let p;

    	const block = {
    		c: function create() {
    			p = element("p");
    			p.textContent = "no room selected";
    			attr_dev(p, "class", "info svelte-13wjb18");
    			add_location(p, file$5, 186, 5, 4716);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block_1$1.name,
    		type: "else",
    		source: "(186:4) {:else}",
    		ctx
    	});

    	return block;
    }

    // (184:4) {#if selected_room_id != -1}
    function create_if_block$3(ctx) {
    	let p;

    	const block = {
    		c: function create() {
    			p = element("p");
    			p.textContent = "no messages, be the first one";
    			attr_dev(p, "class", "info svelte-13wjb18");
    			add_location(p, file$5, 184, 5, 4649);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block$3.name,
    		type: "if",
    		source: "(184:4) {#if selected_room_id != -1}",
    		ctx
    	});

    	return block;
    }

    // (179:3) {#each messages_room_id as message}
    function create_each_block$2(ctx) {
    	let li;
    	let strong;
    	let t0_value = /*message*/ ctx[27].sender + "";
    	let t0;
    	let t1;
    	let t2_value = /*message*/ ctx[27].message + "";
    	let t2;
    	let t3;

    	const block = {
    		c: function create() {
    			li = element("li");
    			strong = element("strong");
    			t0 = text(t0_value);
    			t1 = text(": ");
    			t2 = text(t2_value);
    			t3 = space();
    			attr_dev(strong, "class", "svelte-13wjb18");
    			add_location(strong, file$5, 180, 6, 4536);
    			attr_dev(li, "class", "one_message svelte-13wjb18");
    			toggle_class(li, "servermsg", /*message*/ ctx[27].sender === 'server');
    			add_location(li, file$5, 179, 5, 4459);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, li, anchor);
    			append_dev(li, strong);
    			append_dev(strong, t0);
    			append_dev(li, t1);
    			append_dev(li, t2);
    			append_dev(li, t3);
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*messages_room_id*/ 4 && t0_value !== (t0_value = /*message*/ ctx[27].sender + "")) set_data_dev(t0, t0_value);
    			if (dirty[0] & /*messages_room_id*/ 4 && t2_value !== (t2_value = /*message*/ ctx[27].message + "")) set_data_dev(t2, t2_value);

    			if (dirty[0] & /*messages_room_id*/ 4) {
    				toggle_class(li, "servermsg", /*message*/ ctx[27].sender === 'server');
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(li);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_each_block$2.name,
    		type: "each",
    		source: "(179:3) {#each messages_room_id as message}",
    		ctx
    	});

    	return block;
    }

    function create_fragment$5(ctx) {
    	let verif;
    	let t0;
    	let div2;
    	let div0;
    	let t1;
    	let div1;
    	let ul;
    	let t2;
    	let form;
    	let input;
    	let t3;
    	let button;
    	let current;
    	let mounted;
    	let dispose;

    	verif = new Leave_verif({
    			props: {
    				id: /*data*/ ctx[0].id,
    				roomId: /*roomId*/ ctx[5],
    				verifTab: /*verifTab*/ ctx[4]
    			},
    			$$inline: true
    		});

    	verif.$on("leaving", /*leaving_handler*/ ctx[14]);
    	verif.$on("click", /*click_handler*/ ctx[15]);

    	let info = {
    		ctx,
    		current: null,
    		token: null,
    		hasCatch: false,
    		pending: create_pending_block$3,
    		then: create_then_block$3,
    		catch: create_catch_block$3
    	};

    	handle_promise(reloadRooms(), info);
    	let each_value = /*messages_room_id*/ ctx[2];
    	validate_each_argument(each_value);
    	let each_blocks = [];

    	for (let i = 0; i < each_value.length; i += 1) {
    		each_blocks[i] = create_each_block$2(get_each_context$2(ctx, each_value, i));
    	}

    	let each_1_else_1 = null;

    	if (!each_value.length) {
    		each_1_else_1 = create_else_block$1(ctx);
    	}

    	const block = {
    		c: function create() {
    			create_component(verif.$$.fragment);
    			t0 = space();
    			div2 = element("div");
    			div0 = element("div");
    			info.block.c();
    			t1 = space();
    			div1 = element("div");
    			ul = element("ul");

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				each_blocks[i].c();
    			}

    			if (each_1_else_1) {
    				each_1_else_1.c();
    			}

    			t2 = space();
    			form = element("form");
    			input = element("input");
    			t3 = space();
    			button = element("button");
    			button.textContent = "send";
    			attr_dev(div0, "class", "list_box svelte-13wjb18");
    			add_location(div0, file$5, 157, 1, 3760);
    			attr_dev(ul, "class", "messages svelte-13wjb18");
    			add_location(ul, file$5, 177, 2, 4393);
    			attr_dev(input, "type", "text");
    			attr_dev(input, "placeholder", "write a message, or shut up");
    			attr_dev(input, "class", "svelte-13wjb18");
    			add_location(input, file$5, 191, 3, 4860);
    			attr_dev(button, "class", "svelte-13wjb18");
    			add_location(button, file$5, 192, 3, 4951);
    			attr_dev(form, "class", "component_send_box svelte-13wjb18");
    			add_location(form, file$5, 190, 2, 4784);
    			attr_dev(div1, "class", "room_wrap svelte-13wjb18");
    			add_location(div1, file$5, 176, 1, 4367);
    			attr_dev(div2, "class", "container svelte-13wjb18");
    			add_location(div2, file$5, 156, 0, 3735);
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			mount_component(verif, target, anchor);
    			insert_dev(target, t0, anchor);
    			insert_dev(target, div2, anchor);
    			append_dev(div2, div0);
    			info.block.m(div0, info.anchor = null);
    			info.mount = () => div0;
    			info.anchor = null;
    			append_dev(div2, t1);
    			append_dev(div2, div1);
    			append_dev(div1, ul);

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				if (each_blocks[i]) {
    					each_blocks[i].m(ul, null);
    				}
    			}

    			if (each_1_else_1) {
    				each_1_else_1.m(ul, null);
    			}

    			append_dev(div1, t2);
    			append_dev(div1, form);
    			append_dev(form, input);
    			set_input_value(input, /*user_message*/ ctx[3]);
    			append_dev(form, t3);
    			append_dev(form, button);
    			current = true;

    			if (!mounted) {
    				dispose = [
    					listen_dev(input, "input", /*input_input_handler*/ ctx[18]),
    					listen_dev(form, "submit", prevent_default(/*sendMessage*/ ctx[8]), false, true, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			const verif_changes = {};
    			if (dirty[0] & /*data*/ 1) verif_changes.id = /*data*/ ctx[0].id;
    			if (dirty[0] & /*roomId*/ 32) verif_changes.roomId = /*roomId*/ ctx[5];
    			if (dirty[0] & /*verifTab*/ 16) verif_changes.verifTab = /*verifTab*/ ctx[4];
    			verif.$set(verif_changes);
    			update_await_block_branch(info, ctx, dirty);

    			if (dirty[0] & /*messages_room_id, selected_room_id*/ 6) {
    				each_value = /*messages_room_id*/ ctx[2];
    				validate_each_argument(each_value);
    				let i;

    				for (i = 0; i < each_value.length; i += 1) {
    					const child_ctx = get_each_context$2(ctx, each_value, i);

    					if (each_blocks[i]) {
    						each_blocks[i].p(child_ctx, dirty);
    					} else {
    						each_blocks[i] = create_each_block$2(child_ctx);
    						each_blocks[i].c();
    						each_blocks[i].m(ul, null);
    					}
    				}

    				for (; i < each_blocks.length; i += 1) {
    					each_blocks[i].d(1);
    				}

    				each_blocks.length = each_value.length;

    				if (!each_value.length && each_1_else_1) {
    					each_1_else_1.p(ctx, dirty);
    				} else if (!each_value.length) {
    					each_1_else_1 = create_else_block$1(ctx);
    					each_1_else_1.c();
    					each_1_else_1.m(ul, null);
    				} else if (each_1_else_1) {
    					each_1_else_1.d(1);
    					each_1_else_1 = null;
    				}
    			}

    			if (dirty[0] & /*user_message*/ 8 && input.value !== /*user_message*/ ctx[3]) {
    				set_input_value(input, /*user_message*/ ctx[3]);
    			}
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(verif.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(verif.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(verif, detaching);
    			if (detaching) detach_dev(t0);
    			if (detaching) detach_dev(div2);
    			info.block.d();
    			info.token = null;
    			info = null;
    			destroy_each(each_blocks, detaching);
    			if (each_1_else_1) each_1_else_1.d();
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$5.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$5($$self, $$props, $$invalidate) {
    	let $rooms;
    	validate_store(rooms$1, 'rooms');
    	component_subscribe($$self, rooms$1, $$value => $$invalidate(6, $rooms = $$value));
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Chat', slots, []);
    	let { data } = $$props;
    	let { socket } = $$props;

    	// let channel;
    	//usefull var
    	let username = data.name;

    	//State Variables
    	let selected_room_id = -1;

    	let messages_room_id = [];
    	let messages = [];
    	let members = [];
    	let whoami; // variable qui contient notre status dans la room (owner/admin/user)

    	//bind variable
    	let user_message = "";

    	onMount(() => {
    		deleteSocketEvents();
    		socket.chat.on('serverToChat', recieveMessage); // on defini le comportement lors de l'event mais cette en sauvegardant le message
    		socket.chat.on('serverMessage', recieveServerMessage);
    	});

    	onDestroy(() => {
    		socket.chat.off('serverToChat', recieveMessage);
    		defineSocketEvents();
    	});

    	async function fetchMessages(id) {
    		try {
    			const response = await fetch(`http://${hostname}:3000/chat/messages/${id}`);
    			let rjson = await response.json();
    			messages.push({ room_id: id, msg_content: rjson });
    			$$invalidate(2, messages_room_id = rjson);
    		} catch(error) {
    			console.error(error);
    		}
    	}

    	async function fetchMembers(room_id) {
    		try {
    			const response = await fetch(`http://${hostname}:3000/chat/room/${room_id}`);
    			let rjson = await response.json();
    			console.log(rjson);
    			let me = rjson.find(el => el.member.id == data.id); // on cherche le member qui est nous meme pour en extraire la secu
    			if (me) whoami = me.secu; else whoami = 6; // au cas ou
    			return rjson;
    		} catch(error) {
    			console.error(error);
    		}
    	}

    	//Methods
    	let changeSelectedId = id => {
    		if (selected_room_id != id) $$invalidate(3, user_message = "");
    		$$invalidate(1, selected_room_id = id);
    		deleteAlertOn(id);
    	};

    	let sendMessage = () => {
    		socket.chat.emit('chatToServer', {
    			channel: selected_room_id,
    			sender: username,
    			message: user_message,
    			sender_id: data.id42
    		});

    		$$invalidate(3, user_message = "");
    	};

    	let recieveMessage = msg => {

    		messages.forEach(e => {
    			if (e.room_id == msg.channel) {
    				e.msg_content.push({ sender: msg.sender, message: msg.message });
    			}
    		});

    		$$invalidate(12, messages);
    		if (msg.channel != selected_room_id) newMessage(msg);
    	};

    	let recieveServerMessage = msg => {
    		console.log(msg);

    		messages.forEach(e => {
    			if (e.room_id == msg.channel) {
    				e.msg_content.push({ sender: "server", message: msg.message });
    			}
    		});

    		$$invalidate(12, messages);
    		if (msg.channel != selected_room_id) newMessage(msg);
    	};

    	let deleteAlertOn = roomId => {
    		set_store_value(
    			rooms$1,
    			$rooms = $rooms.map(item => {
    				if (item.roomId === roomId) return { ...item, newMsgCount: 0 };
    				return item;
    			}),
    			$rooms
    		);
    	};

    	let verifTab = false;

    	function verification() {
    		$$invalidate(4, verifTab = !verifTab);
    	}

    	let roomId;

    	async function leaveRoom(room) {
    		$$invalidate(5, roomId = room.roomId);

    		//		await reloadRooms();
    		verification();
    	}

    	$$self.$$.on_mount.push(function () {
    		if (data === undefined && !('data' in $$props || $$self.$$.bound[$$self.$$.props['data']])) {
    			console_1$4.warn("<Chat> was created without expected prop 'data'");
    		}

    		if (socket === undefined && !('socket' in $$props || $$self.$$.bound[$$self.$$.props['socket']])) {
    			console_1$4.warn("<Chat> was created without expected prop 'socket'");
    		}
    	});

    	const writable_props = ['data', 'socket'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console_1$4.warn(`<Chat> was created with unknown prop '${key}'`);
    	});

    	function keypress_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	const leaving_handler = () => verification();
    	const click_handler = () => verification();
    	const click_handler_1 = room => leaveRoom(room);
    	const click_handler_2 = room => changeSelectedId(room.roomId);

    	function input_input_handler() {
    		user_message = this.value;
    		$$invalidate(3, user_message);
    	}

    	$$self.$$set = $$props => {
    		if ('data' in $$props) $$invalidate(0, data = $$props.data);
    		if ('socket' in $$props) $$invalidate(11, socket = $$props.socket);
    	};

    	$$self.$capture_state = () => ({
    		io: lookup,
    		onDestroy,
    		onMount,
    		hostname,
    		rooms: rooms$1,
    		reloadRooms,
    		newMessage,
    		defineSocketEvents,
    		deleteSocketEvents,
    		get: get_store_value,
    		set_data,
    		writable,
    		Invitation,
    		ConnectStatus,
    		Verif: Leave_verif,
    		data,
    		socket,
    		username,
    		selected_room_id,
    		messages_room_id,
    		messages,
    		members,
    		whoami,
    		user_message,
    		fetchMessages,
    		fetchMembers,
    		changeSelectedId,
    		sendMessage,
    		recieveMessage,
    		recieveServerMessage,
    		deleteAlertOn,
    		verifTab,
    		verification,
    		roomId,
    		leaveRoom,
    		$rooms
    	});

    	$$self.$inject_state = $$props => {
    		if ('data' in $$props) $$invalidate(0, data = $$props.data);
    		if ('socket' in $$props) $$invalidate(11, socket = $$props.socket);
    		if ('username' in $$props) username = $$props.username;
    		if ('selected_room_id' in $$props) $$invalidate(1, selected_room_id = $$props.selected_room_id);
    		if ('messages_room_id' in $$props) $$invalidate(2, messages_room_id = $$props.messages_room_id);
    		if ('messages' in $$props) $$invalidate(12, messages = $$props.messages);
    		if ('members' in $$props) members = $$props.members;
    		if ('whoami' in $$props) whoami = $$props.whoami;
    		if ('user_message' in $$props) $$invalidate(3, user_message = $$props.user_message);
    		if ('changeSelectedId' in $$props) $$invalidate(7, changeSelectedId = $$props.changeSelectedId);
    		if ('sendMessage' in $$props) $$invalidate(8, sendMessage = $$props.sendMessage);
    		if ('recieveMessage' in $$props) recieveMessage = $$props.recieveMessage;
    		if ('recieveServerMessage' in $$props) recieveServerMessage = $$props.recieveServerMessage;
    		if ('deleteAlertOn' in $$props) deleteAlertOn = $$props.deleteAlertOn;
    		if ('verifTab' in $$props) $$invalidate(4, verifTab = $$props.verifTab);
    		if ('roomId' in $$props) $$invalidate(5, roomId = $$props.roomId);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	$$self.$$.update = () => {
    		if ($$self.$$.dirty[0] & /*messages, selected_room_id*/ 4098) {
    			{
    				let tmp = messages.filter(data => data.room_id == selected_room_id);
    				if (tmp.length) $$invalidate(2, messages_room_id = tmp[0].msg_content); else if (selected_room_id == -1) $$invalidate(2, messages_room_id = []); else fetchMessages(selected_room_id);
    			}
    		}

    		if ($$self.$$.dirty[0] & /*selected_room_id*/ 2) {
    			{
    				members = fetchMembers(selected_room_id);
    			}
    		}
    	};

    	return [
    		data,
    		selected_room_id,
    		messages_room_id,
    		user_message,
    		verifTab,
    		roomId,
    		$rooms,
    		changeSelectedId,
    		sendMessage,
    		verification,
    		leaveRoom,
    		socket,
    		messages,
    		keypress_handler,
    		leaving_handler,
    		click_handler,
    		click_handler_1,
    		click_handler_2,
    		input_input_handler
    	];
    }

    class Chat extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$5, create_fragment$5, safe_not_equal, { data: 0, socket: 11 }, null, [-1, -1]);

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Chat",
    			options,
    			id: create_fragment$5.name
    		});
    	}

    	get data() {
    		throw new Error("<Chat>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set data(value) {
    		throw new Error("<Chat>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	get socket() {
    		throw new Error("<Chat>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set socket(value) {
    		throw new Error("<Chat>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/component/game/pong.svelte generated by Svelte v3.59.1 */

    const { console: console_1$3 } = globals;
    const file$4 = "src/component/game/pong.svelte";

    // (1:0) <script>     import { browser }
    function create_catch_block$2(ctx) {
    	const block = { c: noop$1, m: noop$1, p: noop$1, d: noop$1 };

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_catch_block$2.name,
    		type: "catch",
    		source: "(1:0) <script>     import { browser }",
    		ctx
    	});

    	return block;
    }

    // (198:0) {:then test}
    function create_then_block$2(ctx) {
    	let button;
    	let mounted;
    	let dispose;

    	const block = {
    		c: function create() {
    			button = element("button");
    			button.textContent = "init game";
    			add_location(button, file$4, 198, 1, 4528);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, button, anchor);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", /*initGame*/ ctx[7], false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_then_block$2.name,
    		type: "then",
    		source: "(198:0) {:then test}",
    		ctx
    	});

    	return block;
    }

    // (196:16)   <p>attente</p> {:then test}
    function create_pending_block$2(ctx) {
    	let p;

    	const block = {
    		c: function create() {
    			p = element("p");
    			p.textContent = "attente";
    			add_location(p, file$4, 196, 1, 4498);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_pending_block$2.name,
    		type: "pending",
    		source: "(196:16)   <p>attente</p> {:then test}",
    		ctx
    	});

    	return block;
    }

    function create_fragment$4(ctx) {
    	let promise_1;
    	let t0;
    	let main;
    	let body;
    	let div3;
    	let div2;
    	let h10;
    	let t2;
    	let button0;
    	let t4;
    	let div0;
    	let t6;
    	let div1;
    	let input_1;
    	let t7;
    	let button1;
    	let t9;
    	let div4;
    	let h11;
    	let t10;
    	let span;
    	let t11;
    	let canvas_1;
    	let mounted;
    	let dispose;

    	let info = {
    		ctx,
    		current: null,
    		token: null,
    		hasCatch: false,
    		pending: create_pending_block$2,
    		then: create_then_block$2,
    		catch: create_catch_block$2,
    		value: 31
    	};

    	handle_promise(promise_1 = /*promise*/ ctx[4], info);

    	const block = {
    		c: function create() {
    			info.block.c();
    			t0 = space();
    			main = element("main");
    			body = element("body");
    			div3 = element("div");
    			div2 = element("div");
    			h10 = element("h1");
    			h10.textContent = "Multiplayer Pong Game";
    			t2 = space();
    			button0 = element("button");
    			button0.textContent = "Create New Game";
    			t4 = space();
    			div0 = element("div");
    			div0.textContent = "OR";
    			t6 = space();
    			div1 = element("div");
    			input_1 = element("input");
    			t7 = space();
    			button1 = element("button");
    			button1.textContent = "Join Game";
    			t9 = space();
    			div4 = element("div");
    			h11 = element("h1");
    			t10 = text("Your game code is: ");
    			span = element("span");
    			t11 = space();
    			canvas_1 = element("canvas");
    			add_location(h10, file$4, 205, 12, 4748);
    			attr_dev(button0, "class", "btn btn-success");
    			attr_dev(button0, "id", "newGameBtn");
    			add_location(button0, file$4, 206, 12, 4791);
    			add_location(div0, file$4, 209, 12, 4934);
    			attr_dev(input_1, "placeholder", "enter your name");
    			add_location(input_1, file$4, 211, 4, 4989);
    			attr_dev(div1, "class", "form-group");
    			add_location(div1, file$4, 210, 12, 4960);
    			attr_dev(button1, "class", "btn btn-success");
    			attr_dev(button1, "id", "joinGameBtn");
    			add_location(button1, file$4, 213, 12, 5079);
    			attr_dev(div2, "class", "d-flex flex-column align-items-center justify-content-center h-100");
    			add_location(div2, file$4, 204, 8, 4655);
    			attr_dev(div3, "class", "h-100");
    			add_location(div3, file$4, 203, 1, 4601);
    			attr_dev(span, "id", "gameCode");
    			add_location(span, file$4, 220, 26, 5293);
    			add_location(h11, file$4, 220, 3, 5270);
    			attr_dev(canvas_1, "id", "pong");
    			attr_dev(canvas_1, "width", "600");
    			attr_dev(canvas_1, "height", "400");
    			attr_dev(canvas_1, "class", "svelte-1oa4n5t");
    			add_location(canvas_1, file$4, 222, 8, 5335);
    			attr_dev(div4, "id", "game");
    			attr_dev(div4, "class", "svelte-1oa4n5t");
    			add_location(div4, file$4, 218, 4, 5233);
    			attr_dev(body, "class", "svelte-1oa4n5t");
    			add_location(body, file$4, 202, 1, 4593);
    			add_location(main, file$4, 201, 0, 4585);
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			info.block.m(target, info.anchor = anchor);
    			info.mount = () => t0.parentNode;
    			info.anchor = t0;
    			insert_dev(target, t0, anchor);
    			insert_dev(target, main, anchor);
    			append_dev(main, body);
    			append_dev(body, div3);
    			append_dev(div3, div2);
    			append_dev(div2, h10);
    			append_dev(div2, t2);
    			append_dev(div2, button0);
    			append_dev(div2, t4);
    			append_dev(div2, div0);
    			append_dev(div2, t6);
    			append_dev(div2, div1);
    			append_dev(div1, input_1);
    			set_input_value(input_1, /*input*/ ctx[0]);
    			append_dev(div2, t7);
    			append_dev(div2, button1);
    			/*div3_binding*/ ctx[11](div3);
    			append_dev(body, t9);
    			append_dev(body, div4);
    			append_dev(div4, h11);
    			append_dev(h11, t10);
    			append_dev(h11, span);
    			append_dev(div4, t11);
    			append_dev(div4, canvas_1);
    			/*canvas_1_binding*/ ctx[12](canvas_1);
    			/*div4_binding*/ ctx[13](div4);

    			if (!mounted) {
    				dispose = [
    					listen_dev(button0, "click", /*handleCreateGame*/ ctx[5], false, false, false, false),
    					listen_dev(input_1, "input", /*input_1_input_handler*/ ctx[10]),
    					listen_dev(button1, "click", /*handleJoinGame*/ ctx[6], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			info.ctx = ctx;

    			if (dirty[0] & /*promise*/ 16 && promise_1 !== (promise_1 = /*promise*/ ctx[4]) && handle_promise(promise_1, info)) ; else {
    				update_await_block_branch(info, ctx, dirty);
    			}

    			if (dirty[0] & /*input*/ 1 && input_1.value !== /*input*/ ctx[0]) {
    				set_input_value(input_1, /*input*/ ctx[0]);
    			}
    		},
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			info.block.d(detaching);
    			info.token = null;
    			info = null;
    			if (detaching) detach_dev(t0);
    			if (detaching) detach_dev(main);
    			/*div3_binding*/ ctx[11](null);
    			/*canvas_1_binding*/ ctx[12](null);
    			/*div4_binding*/ ctx[13](null);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$4.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$4($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Pong', slots, []);
    	let client;
    	let name;
    	let input;
    	let initialScreen;
    	let canvas;
    	let ctx;
    	let game;
    	let pong;
    	let room;
    	let gameActive = false;
    	let promise;
    	let gameCode;
    	let playerNumber;

    	if (environment.browser) {
    		client = new colyseus_js.Client("ws://" + location.hostname + ":3001");
    	}

    	async function createGame() {
    		try {
    			$$invalidate(8, room = await client?.joinOrCreate("my_room")); // this will create "my_room" if it doesn't exist already or join it if it does exist
    			name = room.id;
    			return room.id;
    		} catch(e) {
    			console.error(e);
    		}
    	}

    	const handleCreateGame = () => {
    		$$invalidate(4, promise = createGame());
    	};

    	async function joinGame() {
    		try {
    			console.log(input);
    			$$invalidate(8, room = await client?.joinById(input));
    		} catch(e) {
    			console.error(e);
    		}
    	}

    	const handleJoinGame = () => {
    		$$invalidate(4, promise = joinGame());
    	};

    	function init() {
    		console.log("dans init");
    		$$invalidate(1, initialScreen.style.display = "none", initialScreen);
    		$$invalidate(2, game.style.display = "block", game);
    		canvas = pong;
    		ctx = canvas.getContext('2d');
    		gameCode = document.getElementById('gameCode');
    		gameCode.innerText = name;
    		gameActive = true;
    		console.log(gameCode);
    		document.addEventListener('keydown', keydown);
    		document.addEventListener('keyup', keyup);
    	} //gameActive = true;

    	function keydown(e) {
    		console.log("keydown");
    		console.log(e.keyCode);

    		if (e.keyCode === 38) {
    			if (playerNumber == 1) room.send("keydown38player1"); else room.send("keydown38player2");
    		}

    		if (e.keyCode === 40) {
    			if (playerNumber == 1) room.send("keydown40player1"); else room.send("keydown40player2");
    		}
    	}

    	function keyup(e) {
    		console.log("keyup");
    		console.log(e.keyCode);

    		if (e.keyCode === 38) {
    			if (playerNumber == 1) room.send("keyup38player1"); else room.send("keyup38player2");
    		}

    		if (e.keyCode === 40) {
    			if (playerNumber == 1) room.send("keyup40player1"); else room.send("keyup40player2");
    		}
    	}

    	const initGame = () => {
    		// room?.send("init");
    		$$invalidate(4, promise = init());

    		console.log(name);
    	};

    	//function setupMessageHandlers() {
    	// room?.onMessage("gameState", handleGameState);
    	// room?.onMessage("gameCode", handleGameCode);
    	// room?.onMessage("unknownCode", handleUnknownCode);
    	// room?.onMessage("tooManyPlayers", handleTooManyPlayers);
    	// room?.onMessage("playerNumber", handlePlayerNumber);
    	//}
    	// room?.onMessage("init2", () => {
    	// 	console.log('test init2!')
    	// });
    	function drawRect(x, y, w, h, color) {
    		ctx.fillStyle = color;
    		ctx.fillRect(x, y, w, h);
    	}

    	function drawArc(x, y, r, color) {
    		ctx.fillStyle = color;
    		ctx.beginPath();
    		ctx.arc(x, y, r, 0, Math.PI * 2, true);
    		ctx.closePath();
    		ctx.fill();
    	}

    	function drawNet(statenet) {
    		for (let i = 0; i <= canvas.height; i += 15) {
    			drawRect(statenet.net.x, statenet.net.y + i, statenet.net.width, statenet.net.height, statenet.net.color);
    		}
    	}

    	function drawText(text, x, y) {
    		ctx.fillStyle = "#FFF";
    		ctx.font = "75px fantasy";
    		ctx.fillText(text, x, y);
    	}

    	function trender(state) {
    		drawRect(0, 0, canvas.width, canvas.height, "#000");
    		drawText(state.user.score, canvas.width / 4, canvas.height / 5);
    		drawText(state.com.score, 3 * canvas.width / 4, canvas.height / 5);
    		drawNet(state);
    		drawRect(state.user.x, state.user.y, state.user.width, state.user.height, state.user.color);
    		drawRect(state.com.x, state.com.y, state.com.width, state.com.height, state.com.color);
    		drawArc(state.ball.x, state.ball.y, state.ball.radius, state.ball.color);
    	}

    	function handleGameState(gameState) {
    		if (!gameActive) {
    			return;
    		}

    		gameState = JSON.parse(gameState);
    		requestAnimationFrame(() => trender(gameState));
    	}

    	const writable_props = [];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console_1$3.warn(`<Pong> was created with unknown prop '${key}'`);
    	});

    	function input_1_input_handler() {
    		input = this.value;
    		$$invalidate(0, input);
    	}

    	function div3_binding($$value) {
    		binding_callbacks[$$value ? 'unshift' : 'push'](() => {
    			initialScreen = $$value;
    			$$invalidate(1, initialScreen);
    		});
    	}

    	function canvas_1_binding($$value) {
    		binding_callbacks[$$value ? 'unshift' : 'push'](() => {
    			pong = $$value;
    			$$invalidate(3, pong);
    		});
    	}

    	function div4_binding($$value) {
    		binding_callbacks[$$value ? 'unshift' : 'push'](() => {
    			game = $$value;
    			$$invalidate(2, game);
    		});
    	}

    	$$self.$capture_state = () => ({
    		browser: environment.browser,
    		Client: colyseus_js.Client,
    		onMount,
    		client,
    		name,
    		input,
    		initialScreen,
    		canvas,
    		ctx,
    		game,
    		pong,
    		room,
    		gameActive,
    		promise,
    		gameCode,
    		playerNumber,
    		createGame,
    		handleCreateGame,
    		joinGame,
    		handleJoinGame,
    		init,
    		keydown,
    		keyup,
    		initGame,
    		drawRect,
    		drawArc,
    		drawNet,
    		drawText,
    		trender,
    		handleGameState
    	});

    	$$self.$inject_state = $$props => {
    		if ('client' in $$props) client = $$props.client;
    		if ('name' in $$props) name = $$props.name;
    		if ('input' in $$props) $$invalidate(0, input = $$props.input);
    		if ('initialScreen' in $$props) $$invalidate(1, initialScreen = $$props.initialScreen);
    		if ('canvas' in $$props) canvas = $$props.canvas;
    		if ('ctx' in $$props) ctx = $$props.ctx;
    		if ('game' in $$props) $$invalidate(2, game = $$props.game);
    		if ('pong' in $$props) $$invalidate(3, pong = $$props.pong);
    		if ('room' in $$props) $$invalidate(8, room = $$props.room);
    		if ('gameActive' in $$props) gameActive = $$props.gameActive;
    		if ('promise' in $$props) $$invalidate(4, promise = $$props.promise);
    		if ('gameCode' in $$props) gameCode = $$props.gameCode;
    		if ('playerNumber' in $$props) $$invalidate(9, playerNumber = $$props.playerNumber);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	$$self.$$.update = () => {
    		if ($$self.$$.dirty[0] & /*room, playerNumber*/ 768) {
    			if (room) {
    				room.onMessage("init", j => {
    					$$invalidate(9, playerNumber = j);
    					console.log(playerNumber);

    					//console.log('test init22! ' + name + ' ' + room.id);
    					//console.log("client id: " + client.id);
    					console.log('init');
    				});

    				room.onMessage("gameState", gameState => {
    					//console.log('test gameState');
    					gameState = JSON.parse(gameState);

    					requestAnimationFrame(() => trender(gameState));
    				});

    				room.onMessage("gameOver", data => {
    					let date = JSON.parse(data);

    					if (date.winner === playerNumber) {
    						alert('You win!');
    					} else {
    						alert('You lose!');
    					}
    				});
    			}
    		}
    	};

    	return [
    		input,
    		initialScreen,
    		game,
    		pong,
    		promise,
    		handleCreateGame,
    		handleJoinGame,
    		initGame,
    		room,
    		playerNumber,
    		input_1_input_handler,
    		div3_binding,
    		canvas_1_binding,
    		div4_binding
    	];
    }

    class Pong extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$4, create_fragment$4, safe_not_equal, {}, null, [-1, -1]);

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Pong",
    			options,
    			id: create_fragment$4.name
    		});
    	}
    }

    /* src/component/rooms/delete_resign.svelte generated by Svelte v3.59.1 */

    const { console: console_1$2 } = globals;
    const file$3 = "src/component/rooms/delete_resign.svelte";

    function get_each_context$1(ctx, list, i) {
    	const child_ctx = ctx.slice();
    	child_ctx[28] = list[i];
    	return child_ctx;
    }

    function get_each_context_1$1(ctx, list, i) {
    	const child_ctx = ctx.slice();
    	child_ctx[31] = list[i];
    	return child_ctx;
    }

    // (168:1) {:catch error}
    function create_catch_block$1(ctx) {
    	let p;
    	let t0;
    	let t1_value = /*error*/ ctx[34].message + "";
    	let t1;

    	const block = {
    		c: function create() {
    			p = element("p");
    			t0 = text("Une erreur s'est prosuite ");
    			t1 = text(t1_value);
    			add_location(p, file$3, 168, 2, 3683);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    			append_dev(p, t0);
    			append_dev(p, t1);
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_catch_block$1.name,
    		type: "catch",
    		source: "(168:1) {:catch error}",
    		ctx
    	});

    	return block;
    }

    // (113:1) {:then}
    function create_then_block$1(ctx) {
    	let if_block_anchor;

    	function select_block_type(ctx, dirty) {
    		if (/*delTab*/ ctx[0] === 'res' && ((!/*admins*/ ctx[1] || /*admins*/ ctx[1].length === 0) && (!/*members*/ ctx[2] || /*members*/ ctx[2].length === 0))) return create_if_block$2;
    		if (/*delTab*/ ctx[0] === 'del') return create_if_block_1$2;
    		if (/*delTab*/ ctx[0] === 'res') return create_if_block_2$2;
    	}

    	let current_block_type = select_block_type(ctx);
    	let if_block = current_block_type && current_block_type(ctx);

    	const block = {
    		c: function create() {
    			if (if_block) if_block.c();
    			if_block_anchor = empty$1();
    		},
    		m: function mount(target, anchor) {
    			if (if_block) if_block.m(target, anchor);
    			insert_dev(target, if_block_anchor, anchor);
    		},
    		p: function update(ctx, dirty) {
    			if (current_block_type === (current_block_type = select_block_type(ctx)) && if_block) {
    				if_block.p(ctx, dirty);
    			} else {
    				if (if_block) if_block.d(1);
    				if_block = current_block_type && current_block_type(ctx);

    				if (if_block) {
    					if_block.c();
    					if_block.m(if_block_anchor.parentNode, if_block_anchor);
    				}
    			}
    		},
    		d: function destroy(detaching) {
    			if (if_block) {
    				if_block.d(detaching);
    			}

    			if (detaching) detach_dev(if_block_anchor);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_then_block$1.name,
    		type: "then",
    		source: "(113:1) {:then}",
    		ctx
    	});

    	return block;
    }

    // (137:30) 
    function create_if_block_2$2(ctx) {
    	let div1;
    	let div0;
    	let t;
    	let mounted;
    	let dispose;
    	let if_block0 = /*admins*/ ctx[1].length > 0 && create_if_block_4$2(ctx);
    	let if_block1 = /*members*/ ctx[2].length > 0 && create_if_block_3$2(ctx);

    	const block = {
    		c: function create() {
    			div1 = element("div");
    			div0 = element("div");
    			if (if_block0) if_block0.c();
    			t = space();
    			if (if_block1) if_block1.c();
    			attr_dev(div0, "class", "modal svelte-1ilhx9i");
    			add_location(div0, file$3, 138, 5, 2816);
    			attr_dev(div1, "class", "backdrop svelte-1ilhx9i");
    			add_location(div1, file$3, 137, 4, 2762);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div1, anchor);
    			append_dev(div1, div0);
    			if (if_block0) if_block0.m(div0, null);
    			append_dev(div0, t);
    			if (if_block1) if_block1.m(div0, null);

    			if (!mounted) {
    				dispose = [
    					listen_dev(div1, "click", self$1(/*click_handler_5*/ ctx[16]), false, false, false, false),
    					listen_dev(div1, "keypress", /*keypress_handler_2*/ ctx[17], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (/*admins*/ ctx[1].length > 0) {
    				if (if_block0) {
    					if_block0.p(ctx, dirty);
    				} else {
    					if_block0 = create_if_block_4$2(ctx);
    					if_block0.c();
    					if_block0.m(div0, t);
    				}
    			} else if (if_block0) {
    				if_block0.d(1);
    				if_block0 = null;
    			}

    			if (/*members*/ ctx[2].length > 0) {
    				if (if_block1) {
    					if_block1.p(ctx, dirty);
    				} else {
    					if_block1 = create_if_block_3$2(ctx);
    					if_block1.c();
    					if_block1.m(div0, null);
    				}
    			} else if (if_block1) {
    				if_block1.d(1);
    				if_block1 = null;
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div1);
    			if (if_block0) if_block0.d();
    			if (if_block1) if_block1.d();
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_2$2.name,
    		type: "if",
    		source: "(137:30) ",
    		ctx
    	});

    	return block;
    }

    // (128:3) {#if delTab === 'del'}
    function create_if_block_1$2(ctx) {
    	let div1;
    	let div0;
    	let h1;
    	let t1;
    	let button0;
    	let t3;
    	let button1;
    	let mounted;
    	let dispose;

    	const block = {
    		c: function create() {
    			div1 = element("div");
    			div0 = element("div");
    			h1 = element("h1");
    			h1.textContent = "Are you sure ?";
    			t1 = space();
    			button0 = element("button");
    			button0.textContent = "yes";
    			t3 = space();
    			button1 = element("button");
    			button1.textContent = "no";
    			add_location(h1, file$3, 130, 5, 2593);
    			add_location(button0, file$3, 131, 5, 2622);
    			add_location(button1, file$3, 132, 5, 2676);
    			attr_dev(div0, "class", "modal svelte-1ilhx9i");
    			add_location(div0, file$3, 129, 4, 2568);
    			attr_dev(div1, "class", "backdrop svelte-1ilhx9i");
    			add_location(div1, file$3, 128, 4, 2515);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div1, anchor);
    			append_dev(div1, div0);
    			append_dev(div0, h1);
    			append_dev(div0, t1);
    			append_dev(div0, button0);
    			append_dev(div0, t3);
    			append_dev(div0, button1);

    			if (!mounted) {
    				dispose = [
    					listen_dev(button0, "click", /*click_handler_7*/ ctx[20], false, false, false, false),
    					listen_dev(button1, "click", /*click_handler_4*/ ctx[15], false, false, false, false),
    					listen_dev(div1, "click", self$1(/*click_handler_3*/ ctx[13]), false, false, false, false),
    					listen_dev(div1, "keypress", /*keypress_handler_1*/ ctx[14], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div1);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_1$2.name,
    		type: "if",
    		source: "(128:3) {#if delTab === 'del'}",
    		ctx
    	});

    	return block;
    }

    // (114:2) {#if delTab === 'res'   && ((!admins || admins.length === 0)    && (!members || members.length === 0))}
    function create_if_block$2(ctx) {
    	let div1;
    	let div0;
    	let h1;
    	let t1;
    	let p;
    	let t3;
    	let button0;
    	let t5;
    	let button1;
    	let mounted;
    	let dispose;

    	const block = {
    		c: function create() {
    			div1 = element("div");
    			div0 = element("div");
    			h1 = element("h1");
    			h1.textContent = "empty room";
    			t1 = space();
    			p = element("p");
    			p.textContent = "do you want to delete it ?";
    			t3 = space();
    			button0 = element("button");
    			button0.textContent = "yes";
    			t5 = space();
    			button1 = element("button");
    			button1.textContent = "no";
    			add_location(h1, file$3, 119, 5, 2303);
    			add_location(p, file$3, 120, 5, 2328);
    			add_location(button0, file$3, 121, 5, 2367);
    			add_location(button1, file$3, 122, 5, 2421);
    			attr_dev(div0, "class", "modal svelte-1ilhx9i");
    			add_location(div0, file$3, 118, 4, 2278);
    			attr_dev(div1, "class", "backdrop svelte-1ilhx9i");
    			add_location(div1, file$3, 117, 3, 2225);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div1, anchor);
    			append_dev(div1, div0);
    			append_dev(div0, h1);
    			append_dev(div0, t1);
    			append_dev(div0, p);
    			append_dev(div0, t3);
    			append_dev(div0, button0);
    			append_dev(div0, t5);
    			append_dev(div0, button1);

    			if (!mounted) {
    				dispose = [
    					listen_dev(button0, "click", /*click_handler_6*/ ctx[19], false, false, false, false),
    					listen_dev(button1, "click", /*click_handler_2*/ ctx[12], false, false, false, false),
    					listen_dev(div1, "click", self$1(/*click_handler_1*/ ctx[10]), false, false, false, false),
    					listen_dev(div1, "keypress", /*keypress_handler*/ ctx[11], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div1);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block$2.name,
    		type: "if",
    		source: "(114:2) {#if delTab === 'res'   && ((!admins || admins.length === 0)    && (!members || members.length === 0))}",
    		ctx
    	});

    	return block;
    }

    // (140:6) {#if admins.length > 0}
    function create_if_block_4$2(ctx) {
    	let h1;
    	let t1;
    	let label0;
    	let input0;
    	let input0_checked_value;
    	let t2;
    	let t3;
    	let label1;
    	let input1;
    	let input1_checked_value;
    	let t4;
    	let t5;
    	let h3;
    	let t7;
    	let each_1_anchor;
    	let mounted;
    	let dispose;
    	let each_value_1 = /*admins*/ ctx[1];
    	validate_each_argument(each_value_1);
    	let each_blocks = [];

    	for (let i = 0; i < each_value_1.length; i += 1) {
    		each_blocks[i] = create_each_block_1$1(get_each_context_1$1(ctx, each_value_1, i));
    	}

    	const block = {
    		c: function create() {
    			h1 = element("h1");
    			h1.textContent = "To whom do you want to pass ownership ?";
    			t1 = space();
    			label0 = element("label");
    			input0 = element("input");
    			t2 = text("\n\t\t\t\t\t\t\t\tand leave");
    			t3 = space();
    			label1 = element("label");
    			input1 = element("input");
    			t4 = text("\n\t\t\t\t\t\t\t\tand stay");
    			t5 = space();
    			h3 = element("h3");
    			h3.textContent = "admins";
    			t7 = space();

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				each_blocks[i].c();
    			}

    			each_1_anchor = empty$1();
    			add_location(h1, file$3, 140, 7, 2873);
    			attr_dev(input0, "type", "radio");
    			input0.value = "leave";
    			attr_dev(input0, "name", "stayOption");
    			input0.checked = input0_checked_value = /*stayOption*/ ctx[3] === 'leave';
    			add_location(input0, file$3, 142, 8, 2945);
    			add_location(label0, file$3, 141, 7, 2929);
    			attr_dev(input1, "type", "radio");
    			input1.value = "stay";
    			attr_dev(input1, "name", "stayOption");
    			input1.checked = input1_checked_value = /*stayOption*/ ctx[3] === 'stay';
    			add_location(input1, file$3, 146, 8, 3129);
    			add_location(label1, file$3, 145, 7, 3113);
    			add_location(h3, file$3, 150, 7, 3294);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, h1, anchor);
    			insert_dev(target, t1, anchor);
    			insert_dev(target, label0, anchor);
    			append_dev(label0, input0);
    			append_dev(label0, t2);
    			insert_dev(target, t3, anchor);
    			insert_dev(target, label1, anchor);
    			append_dev(label1, input1);
    			append_dev(label1, t4);
    			insert_dev(target, t5, anchor);
    			insert_dev(target, h3, anchor);
    			insert_dev(target, t7, anchor);

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				if (each_blocks[i]) {
    					each_blocks[i].m(target, anchor);
    				}
    			}

    			insert_dev(target, each_1_anchor, anchor);

    			if (!mounted) {
    				dispose = [
    					listen_dev(input0, "change", /*change_handler*/ ctx[21], false, false, false, false),
    					listen_dev(input1, "change", /*change_handler_1*/ ctx[22], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*stayOption*/ 8 && input0_checked_value !== (input0_checked_value = /*stayOption*/ ctx[3] === 'leave')) {
    				prop_dev(input0, "checked", input0_checked_value);
    			}

    			if (dirty[0] & /*stayOption*/ 8 && input1_checked_value !== (input1_checked_value = /*stayOption*/ ctx[3] === 'stay')) {
    				prop_dev(input1, "checked", input1_checked_value);
    			}

    			if (dirty[0] & /*resign, admins*/ 34) {
    				each_value_1 = /*admins*/ ctx[1];
    				validate_each_argument(each_value_1);
    				let i;

    				for (i = 0; i < each_value_1.length; i += 1) {
    					const child_ctx = get_each_context_1$1(ctx, each_value_1, i);

    					if (each_blocks[i]) {
    						each_blocks[i].p(child_ctx, dirty);
    					} else {
    						each_blocks[i] = create_each_block_1$1(child_ctx);
    						each_blocks[i].c();
    						each_blocks[i].m(each_1_anchor.parentNode, each_1_anchor);
    					}
    				}

    				for (; i < each_blocks.length; i += 1) {
    					each_blocks[i].d(1);
    				}

    				each_blocks.length = each_value_1.length;
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(h1);
    			if (detaching) detach_dev(t1);
    			if (detaching) detach_dev(label0);
    			if (detaching) detach_dev(t3);
    			if (detaching) detach_dev(label1);
    			if (detaching) detach_dev(t5);
    			if (detaching) detach_dev(h3);
    			if (detaching) detach_dev(t7);
    			destroy_each(each_blocks, detaching);
    			if (detaching) detach_dev(each_1_anchor);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_4$2.name,
    		type: "if",
    		source: "(140:6) {#if admins.length > 0}",
    		ctx
    	});

    	return block;
    }

    // (152:7) {#each admins as admin}
    function create_each_block_1$1(ctx) {
    	let button;
    	let t_value = /*admin*/ ctx[31].name + "";
    	let t;
    	let mounted;
    	let dispose;

    	function click_handler_8() {
    		return /*click_handler_8*/ ctx[23](/*admin*/ ctx[31]);
    	}

    	const block = {
    		c: function create() {
    			button = element("button");
    			t = text(t_value);
    			add_location(button, file$3, 152, 8, 3349);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, button, anchor);
    			append_dev(button, t);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_8, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			if (dirty[0] & /*admins*/ 2 && t_value !== (t_value = /*admin*/ ctx[31].name + "")) set_data_dev(t, t_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_each_block_1$1.name,
    		type: "each",
    		source: "(152:7) {#each admins as admin}",
    		ctx
    	});

    	return block;
    }

    // (157:6) {#if members.length > 0}
    function create_if_block_3$2(ctx) {
    	let h3;
    	let t1;
    	let each_1_anchor;
    	let each_value = /*members*/ ctx[2];
    	validate_each_argument(each_value);
    	let each_blocks = [];

    	for (let i = 0; i < each_value.length; i += 1) {
    		each_blocks[i] = create_each_block$1(get_each_context$1(ctx, each_value, i));
    	}

    	const block = {
    		c: function create() {
    			h3 = element("h3");
    			h3.textContent = "members";
    			t1 = space();

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				each_blocks[i].c();
    			}

    			each_1_anchor = empty$1();
    			add_location(h3, file$3, 157, 7, 3476);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, h3, anchor);
    			insert_dev(target, t1, anchor);

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				if (each_blocks[i]) {
    					each_blocks[i].m(target, anchor);
    				}
    			}

    			insert_dev(target, each_1_anchor, anchor);
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*resign, members*/ 36) {
    				each_value = /*members*/ ctx[2];
    				validate_each_argument(each_value);
    				let i;

    				for (i = 0; i < each_value.length; i += 1) {
    					const child_ctx = get_each_context$1(ctx, each_value, i);

    					if (each_blocks[i]) {
    						each_blocks[i].p(child_ctx, dirty);
    					} else {
    						each_blocks[i] = create_each_block$1(child_ctx);
    						each_blocks[i].c();
    						each_blocks[i].m(each_1_anchor.parentNode, each_1_anchor);
    					}
    				}

    				for (; i < each_blocks.length; i += 1) {
    					each_blocks[i].d(1);
    				}

    				each_blocks.length = each_value.length;
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(h3);
    			if (detaching) detach_dev(t1);
    			destroy_each(each_blocks, detaching);
    			if (detaching) detach_dev(each_1_anchor);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_3$2.name,
    		type: "if",
    		source: "(157:6) {#if members.length > 0}",
    		ctx
    	});

    	return block;
    }

    // (159:7) {#each members as member}
    function create_each_block$1(ctx) {
    	let button;
    	let t_value = /*member*/ ctx[28].name + "";
    	let t;
    	let mounted;
    	let dispose;

    	function click_handler_9() {
    		return /*click_handler_9*/ ctx[24](/*member*/ ctx[28]);
    	}

    	const block = {
    		c: function create() {
    			button = element("button");
    			t = text(t_value);
    			add_location(button, file$3, 159, 8, 3534);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, button, anchor);
    			append_dev(button, t);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_9, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			if (dirty[0] & /*members*/ 4 && t_value !== (t_value = /*member*/ ctx[28].name + "")) set_data_dev(t, t_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_each_block$1.name,
    		type: "each",
    		source: "(159:7) {#each members as member}",
    		ctx
    	});

    	return block;
    }

    // (108:31)    <div class="backdrop" on:click|self on:keypress={() => getReplacementLists()}
    function create_pending_block$1(ctx) {
    	let div;
    	let p;
    	let mounted;
    	let dispose;

    	const block = {
    		c: function create() {
    			div = element("div");
    			p = element("p");
    			p.textContent = "Loading...";
    			add_location(p, file$3, 109, 3, 2076);
    			attr_dev(div, "class", "backdrop svelte-1ilhx9i");
    			add_location(div, file$3, 108, 2, 1994);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div, anchor);
    			append_dev(div, p);

    			if (!mounted) {
    				dispose = [
    					listen_dev(div, "click", self$1(/*click_handler*/ ctx[9]), false, false, false, false),
    					listen_dev(div, "keypress", /*keypress_handler_3*/ ctx[18], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_pending_block$1.name,
    		type: "pending",
    		source: "(108:31)    <div class=\\\"backdrop\\\" on:click|self on:keypress={() => getReplacementLists()}",
    		ctx
    	});

    	return block;
    }

    function create_fragment$3(ctx) {
    	let await_block_anchor;

    	let info = {
    		ctx,
    		current: null,
    		token: null,
    		hasCatch: true,
    		pending: create_pending_block$1,
    		then: create_then_block$1,
    		catch: create_catch_block$1,
    		error: 34
    	};

    	handle_promise(/*getReplacementLists*/ ctx[4](), info);

    	const block = {
    		c: function create() {
    			await_block_anchor = empty$1();
    			info.block.c();
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, await_block_anchor, anchor);
    			info.block.m(target, info.anchor = anchor);
    			info.mount = () => await_block_anchor.parentNode;
    			info.anchor = await_block_anchor;
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			update_await_block_branch(info, ctx, dirty);
    		},
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(await_block_anchor);
    			info.block.d(detaching);
    			info.token = null;
    			info = null;
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$3.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$3($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Delete_resign', slots, []);
    	const dispatch = createEventDispatcher();
    	let { id } = $$props;
    	let { delTab } = $$props;
    	let { roomId } = $$props;
    	let admins = [];
    	let members = [];

    	async function getReplacementLists() {
    		try {
    			const response = await fetch(`http://${hostname}:3000/rooms/replacementList/${roomId}`);

    			if (response.ok) {
    				const data = await response.json();
    				$$invalidate(1, admins = data.admins);
    				$$invalidate(2, members = data.members);
    			} else {
    				console.error('failed to load replacement list');
    			}
    		} catch(error) {
    			console.log(error);
    		}
    	}
    	let firstLoad = true;

    	onMount(async () => {
    		await getReplacementLists();
    		firstLoad = false;
    	});

    	afterUpdate(() => {
    		if (!firstLoad) {
    			getReplacementLists();
    		}
    	});

    	let stayOption = 'stay'; // Default option is "and stay"

    	function handleValidationClick() {
    		dispatch('validationClick');
    	}

    	async function resign(client) {
    		let stay;
    		if (stayOption === 'stay') stay = true; else stay = false;

    		try {
    			const response = await fetch(`http://${hostname}:3000/rooms/resign/${roomId}/${id}/${client.id}/${stay}`, { method: 'POST' });

    			if (response.ok) {
    				console.log(client.name, client.id, stayOption);
    				handleValidationClick();
    			} else {
    				console.error('failed on resign');
    			}
    		} catch(error) {
    			console.error('ERROR: falied on resign', error.message);
    		}
    	}

    	async function eraseRoom() {
    		try {
    			const response = await fetch(`http://${hostname}:3000/rooms/delete/${roomId}`, { method: 'POST' });

    			if (response.ok) {
    				console.log('room id:', roomId, 'deleted');
    				handleValidationClick();
    			} else {
    				console.error('failed on delete', error.message);
    			}
    		} catch(error) {
    			console.error('ERROR: falied on delete', error.message);
    		}
    	}

    	$$self.$$.on_mount.push(function () {
    		if (id === undefined && !('id' in $$props || $$self.$$.bound[$$self.$$.props['id']])) {
    			console_1$2.warn("<Delete_resign> was created without expected prop 'id'");
    		}

    		if (delTab === undefined && !('delTab' in $$props || $$self.$$.bound[$$self.$$.props['delTab']])) {
    			console_1$2.warn("<Delete_resign> was created without expected prop 'delTab'");
    		}

    		if (roomId === undefined && !('roomId' in $$props || $$self.$$.bound[$$self.$$.props['roomId']])) {
    			console_1$2.warn("<Delete_resign> was created without expected prop 'roomId'");
    		}
    	});

    	const writable_props = ['id', 'delTab', 'roomId'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console_1$2.warn(`<Delete_resign> was created with unknown prop '${key}'`);
    	});

    	function click_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	function click_handler_1(event) {
    		bubble.call(this, $$self, event);
    	}

    	function keypress_handler(event) {
    		bubble.call(this, $$self, event);
    	}

    	function click_handler_2(event) {
    		bubble.call(this, $$self, event);
    	}

    	function click_handler_3(event) {
    		bubble.call(this, $$self, event);
    	}

    	function keypress_handler_1(event) {
    		bubble.call(this, $$self, event);
    	}

    	function click_handler_4(event) {
    		bubble.call(this, $$self, event);
    	}

    	function click_handler_5(event) {
    		bubble.call(this, $$self, event);
    	}

    	function keypress_handler_2(event) {
    		bubble.call(this, $$self, event);
    	}

    	const keypress_handler_3 = () => getReplacementLists();
    	const click_handler_6 = () => eraseRoom();
    	const click_handler_7 = () => eraseRoom();
    	const change_handler = () => $$invalidate(3, stayOption = 'leave');
    	const change_handler_1 = () => $$invalidate(3, stayOption = 'stay');
    	const click_handler_8 = admin => resign(admin);
    	const click_handler_9 = member => resign(member);

    	$$self.$$set = $$props => {
    		if ('id' in $$props) $$invalidate(7, id = $$props.id);
    		if ('delTab' in $$props) $$invalidate(0, delTab = $$props.delTab);
    		if ('roomId' in $$props) $$invalidate(8, roomId = $$props.roomId);
    	};

    	$$self.$capture_state = () => ({
    		hostname,
    		onMount,
    		afterUpdate,
    		createEventDispatcher,
    		dispatch,
    		id,
    		delTab,
    		roomId,
    		admins,
    		members,
    		getReplacementLists,
    		firstLoad,
    		stayOption,
    		handleValidationClick,
    		resign,
    		eraseRoom
    	});

    	$$self.$inject_state = $$props => {
    		if ('id' in $$props) $$invalidate(7, id = $$props.id);
    		if ('delTab' in $$props) $$invalidate(0, delTab = $$props.delTab);
    		if ('roomId' in $$props) $$invalidate(8, roomId = $$props.roomId);
    		if ('admins' in $$props) $$invalidate(1, admins = $$props.admins);
    		if ('members' in $$props) $$invalidate(2, members = $$props.members);
    		if ('firstLoad' in $$props) firstLoad = $$props.firstLoad;
    		if ('stayOption' in $$props) $$invalidate(3, stayOption = $$props.stayOption);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [
    		delTab,
    		admins,
    		members,
    		stayOption,
    		getReplacementLists,
    		resign,
    		eraseRoom,
    		id,
    		roomId,
    		click_handler,
    		click_handler_1,
    		keypress_handler,
    		click_handler_2,
    		click_handler_3,
    		keypress_handler_1,
    		click_handler_4,
    		click_handler_5,
    		keypress_handler_2,
    		keypress_handler_3,
    		click_handler_6,
    		click_handler_7,
    		change_handler,
    		change_handler_1,
    		click_handler_8,
    		click_handler_9
    	];
    }

    class Delete_resign extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$3, create_fragment$3, safe_not_equal, { id: 7, delTab: 0, roomId: 8 }, null, [-1, -1]);

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Delete_resign",
    			options,
    			id: create_fragment$3.name
    		});
    	}

    	get id() {
    		throw new Error("<Delete_resign>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set id(value) {
    		throw new Error("<Delete_resign>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	get delTab() {
    		throw new Error("<Delete_resign>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set delTab(value) {
    		throw new Error("<Delete_resign>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	get roomId() {
    		throw new Error("<Delete_resign>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set roomId(value) {
    		throw new Error("<Delete_resign>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/component/rooms/rooms.svelte generated by Svelte v3.59.1 */

    const { Error: Error_1$1, console: console_1$1 } = globals;
    const file$2 = "src/component/rooms/rooms.svelte";

    function get_each_context_2(ctx, list, i) {
    	const child_ctx = ctx.slice();
    	child_ctx[63] = list[i];
    	return child_ctx;
    }

    function get_each_context_3(ctx, list, i) {
    	const child_ctx = ctx.slice();
    	child_ctx[63] = list[i];
    	return child_ctx;
    }

    function get_each_context(ctx, list, i) {
    	const child_ctx = ctx.slice();
    	child_ctx[57] = list[i];
    	return child_ctx;
    }

    function get_each_context_1(ctx, list, i) {
    	const child_ctx = ctx.slice();
    	child_ctx[60] = list[i];
    	return child_ctx;
    }

    // (312:0) {#if delTab}
    function create_if_block_12(ctx) {
    	let delmodal;
    	let current;

    	delmodal = new Delete_resign({
    			props: {
    				delTab: /*delTab*/ ctx[12],
    				roomId: /*choosenRoomId*/ ctx[9],
    				id: /*data*/ ctx[0].id
    			},
    			$$inline: true
    		});

    	delmodal.$on("click", /*click_handler*/ ctx[29]);
    	delmodal.$on("validationClick", /*delReturn*/ ctx[28]);

    	const block = {
    		c: function create() {
    			create_component(delmodal.$$.fragment);
    		},
    		m: function mount(target, anchor) {
    			mount_component(delmodal, target, anchor);
    			current = true;
    		},
    		p: function update(ctx, dirty) {
    			const delmodal_changes = {};
    			if (dirty[0] & /*delTab*/ 4096) delmodal_changes.delTab = /*delTab*/ ctx[12];
    			if (dirty[0] & /*choosenRoomId*/ 512) delmodal_changes.roomId = /*choosenRoomId*/ ctx[9];
    			if (dirty[0] & /*data*/ 1) delmodal_changes.id = /*data*/ ctx[0].id;
    			delmodal.$set(delmodal_changes);
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(delmodal.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(delmodal.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(delmodal, detaching);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_12.name,
    		type: "if",
    		source: "(312:0) {#if delTab}",
    		ctx
    	});

    	return block;
    }

    // (392:2) {:else}
    function create_else_block_2(ctx) {
    	let div0;
    	let h1;
    	let t0;
    	let t1;
    	let center0;
    	let button0;
    	let t3;
    	let t4;
    	let div2;
    	let button1;
    	let t6;
    	let div1;
    	let t7;
    	let div3;
    	let center1;
    	let button2;
    	let t9;
    	let button3;
    	let t11;
    	let mounted;
    	let dispose;
    	let if_block = /*privateRoomMembers*/ ctx[10] && /*privateRoomMembers*/ ctx[10].length !== 0 && create_if_block_11(ctx);
    	let each_value_2 = /*roomMembers*/ ctx[11];
    	validate_each_argument(each_value_2);
    	let each_blocks = [];

    	for (let i = 0; i < each_value_2.length; i += 1) {
    		each_blocks[i] = create_each_block_2(get_each_context_2(ctx, each_value_2, i));
    	}

    	const block = {
    		c: function create() {
    			div0 = element("div");
    			h1 = element("h1");
    			t0 = text(/*choosenRoom*/ ctx[8]);
    			t1 = space();
    			center0 = element("center");
    			button0 = element("button");
    			button0.textContent = "Back";
    			t3 = space();
    			if (if_block) if_block.c();
    			t4 = space();
    			div2 = element("div");
    			button1 = element("button");
    			button1.textContent = "Room Members";
    			t6 = space();
    			div1 = element("div");

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				each_blocks[i].c();
    			}

    			t7 = space();
    			div3 = element("div");
    			center1 = element("center");
    			button2 = element("button");
    			button2.textContent = "Delete room";
    			t9 = text("\n\t\t\t\t/̵͇̿̿/’̿’̿ ̿ ̿̿ ̿̿ ̿̿(╥﹏╥)\n\n\t\t\t\t");
    			button3 = element("button");
    			button3.textContent = "Resign";
    			t11 = text("\n\t\t\t\t(¬ _¬)ﾉ ciao");
    			add_location(h1, file$2, 393, 4, 9199);
    			attr_dev(button0, "class", "toggle-btn svelte-1b3tfzb");
    			add_location(button0, file$2, 394, 12, 9234);
    			add_location(center0, file$2, 394, 4, 9226);
    			attr_dev(div0, "class", "create-container svelte-1b3tfzb");
    			add_location(div0, file$2, 392, 3, 9164);
    			attr_dev(button1, "class", "toggle-btn svelte-1b3tfzb");
    			add_location(button1, file$2, 418, 5, 10007);
    			attr_dev(div1, "class", "room-list svelte-1b3tfzb");
    			add_location(div1, file$2, 419, 5, 10061);
    			attr_dev(div2, "class", "rooms-container svelte-1b3tfzb");
    			add_location(div2, file$2, 417, 4, 9972);
    			attr_dev(button2, "class", "toggle-btn svelte-1b3tfzb");
    			set_style(button2, "background-color", "red");
    			add_location(button2, file$2, 461, 12, 11370);
    			add_location(center1, file$2, 461, 4, 11362);
    			attr_dev(button3, "class", "toggle-btn svelte-1b3tfzb");
    			set_style(button3, "background-color", "red");
    			set_style(button3, "margin-top", "auto");
    			add_location(button3, file$2, 466, 4, 11538);
    			attr_dev(div3, "class", "create-container svelte-1b3tfzb");
    			add_location(div3, file$2, 460, 3, 11327);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div0, anchor);
    			append_dev(div0, h1);
    			append_dev(h1, t0);
    			append_dev(div0, t1);
    			append_dev(div0, center0);
    			append_dev(center0, button0);
    			insert_dev(target, t3, anchor);
    			if (if_block) if_block.m(target, anchor);
    			insert_dev(target, t4, anchor);
    			insert_dev(target, div2, anchor);
    			append_dev(div2, button1);
    			append_dev(div2, t6);
    			append_dev(div2, div1);

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				if (each_blocks[i]) {
    					each_blocks[i].m(div1, null);
    				}
    			}

    			insert_dev(target, t7, anchor);
    			insert_dev(target, div3, anchor);
    			append_dev(div3, center1);
    			append_dev(center1, button2);
    			append_dev(div3, t9);
    			append_dev(div3, button3);
    			append_dev(div3, t11);

    			if (!mounted) {
    				dispose = [
    					listen_dev(button0, "click", /*click_handler_5*/ ctx[37], false, false, false, false),
    					listen_dev(button2, "click", /*click_handler_16*/ ctx[48], false, false, false, false),
    					listen_dev(button3, "click", /*click_handler_17*/ ctx[49], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*choosenRoom*/ 256) set_data_dev(t0, /*choosenRoom*/ ctx[8]);

    			if (/*privateRoomMembers*/ ctx[10] && /*privateRoomMembers*/ ctx[10].length !== 0) {
    				if (if_block) {
    					if_block.p(ctx, dirty);
    				} else {
    					if_block = create_if_block_11(ctx);
    					if_block.c();
    					if_block.m(t4.parentNode, t4);
    				}
    			} else if (if_block) {
    				if_block.d(1);
    				if_block = null;
    			}

    			if (dirty[0] & /*kick, roomMembers, ban, unmute, mute, promote, demote, memberStatusLabels*/ 133171200) {
    				each_value_2 = /*roomMembers*/ ctx[11];
    				validate_each_argument(each_value_2);
    				let i;

    				for (i = 0; i < each_value_2.length; i += 1) {
    					const child_ctx = get_each_context_2(ctx, each_value_2, i);

    					if (each_blocks[i]) {
    						each_blocks[i].p(child_ctx, dirty);
    					} else {
    						each_blocks[i] = create_each_block_2(child_ctx);
    						each_blocks[i].c();
    						each_blocks[i].m(div1, null);
    					}
    				}

    				for (; i < each_blocks.length; i += 1) {
    					each_blocks[i].d(1);
    				}

    				each_blocks.length = each_value_2.length;
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div0);
    			if (detaching) detach_dev(t3);
    			if (if_block) if_block.d(detaching);
    			if (detaching) detach_dev(t4);
    			if (detaching) detach_dev(div2);
    			destroy_each(each_blocks, detaching);
    			if (detaching) detach_dev(t7);
    			if (detaching) detach_dev(div3);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block_2.name,
    		type: "else",
    		source: "(392:2) {:else}",
    		ctx
    	});

    	return block;
    }

    // (321:2) {#if !inspectBoolean}
    function create_if_block$1(ctx) {
    	let t0;
    	let div1;
    	let button0;
    	let t2;
    	let div0;
    	let t3;
    	let div2;
    	let button1;
    	let t5;
    	let mounted;
    	let dispose;
    	let if_block0 = /*ownedRoom*/ ctx[6] && /*ownedRoom*/ ctx[6].length > 0 && create_if_block_5$1(ctx);
    	let each_value = /*rooms*/ ctx[1];
    	validate_each_argument(each_value);
    	let each_blocks = [];

    	for (let i = 0; i < each_value.length; i += 1) {
    		each_blocks[i] = create_each_block(get_each_context(ctx, each_value, i));
    	}

    	let if_block1 = /*isFormVisible*/ ctx[2] && create_if_block_1$1(ctx);

    	const block = {
    		c: function create() {
    			if (if_block0) if_block0.c();
    			t0 = space();
    			div1 = element("div");
    			button0 = element("button");
    			button0.textContent = "List of available rooms";
    			t2 = space();
    			div0 = element("div");

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				each_blocks[i].c();
    			}

    			t3 = space();
    			div2 = element("div");
    			button1 = element("button");
    			button1.textContent = "Create Room";
    			t5 = space();
    			if (if_block1) if_block1.c();
    			attr_dev(button0, "class", "toggle-btn svelte-1b3tfzb");
    			add_location(button0, file$2, 348, 4, 7687);
    			attr_dev(div0, "class", "room-list svelte-1b3tfzb");
    			add_location(div0, file$2, 349, 4, 7751);
    			attr_dev(div1, "class", "rooms-container svelte-1b3tfzb");
    			add_location(div1, file$2, 347, 3, 7653);
    			attr_dev(button1, "class", "create-btn svelte-1b3tfzb");
    			add_location(button1, file$2, 368, 4, 8357);
    			attr_dev(div2, "class", "create-container svelte-1b3tfzb");
    			add_location(div2, file$2, 367, 3, 8322);
    		},
    		m: function mount(target, anchor) {
    			if (if_block0) if_block0.m(target, anchor);
    			insert_dev(target, t0, anchor);
    			insert_dev(target, div1, anchor);
    			append_dev(div1, button0);
    			append_dev(div1, t2);
    			append_dev(div1, div0);

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				if (each_blocks[i]) {
    					each_blocks[i].m(div0, null);
    				}
    			}

    			insert_dev(target, t3, anchor);
    			insert_dev(target, div2, anchor);
    			append_dev(div2, button1);
    			append_dev(div2, t5);
    			if (if_block1) if_block1.m(div2, null);

    			if (!mounted) {
    				dispose = listen_dev(button1, "click", /*toggleForm*/ ctx[13], false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (/*ownedRoom*/ ctx[6] && /*ownedRoom*/ ctx[6].length > 0) {
    				if (if_block0) {
    					if_block0.p(ctx, dirty);
    				} else {
    					if_block0 = create_if_block_5$1(ctx);
    					if_block0.c();
    					if_block0.m(t0.parentNode, t0);
    				}
    			} else if (if_block0) {
    				if_block0.d(1);
    				if_block0 = null;
    			}

    			if (dirty[0] & /*askForPassword, rooms, join*/ 98306) {
    				each_value = /*rooms*/ ctx[1];
    				validate_each_argument(each_value);
    				let i;

    				for (i = 0; i < each_value.length; i += 1) {
    					const child_ctx = get_each_context(ctx, each_value, i);

    					if (each_blocks[i]) {
    						each_blocks[i].p(child_ctx, dirty);
    					} else {
    						each_blocks[i] = create_each_block(child_ctx);
    						each_blocks[i].c();
    						each_blocks[i].m(div0, null);
    					}
    				}

    				for (; i < each_blocks.length; i += 1) {
    					each_blocks[i].d(1);
    				}

    				each_blocks.length = each_value.length;
    			}

    			if (/*isFormVisible*/ ctx[2]) {
    				if (if_block1) {
    					if_block1.p(ctx, dirty);
    				} else {
    					if_block1 = create_if_block_1$1(ctx);
    					if_block1.c();
    					if_block1.m(div2, null);
    				}
    			} else if (if_block1) {
    				if_block1.d(1);
    				if_block1 = null;
    			}
    		},
    		d: function destroy(detaching) {
    			if (if_block0) if_block0.d(detaching);
    			if (detaching) detach_dev(t0);
    			if (detaching) detach_dev(div1);
    			destroy_each(each_blocks, detaching);
    			if (detaching) detach_dev(t3);
    			if (detaching) detach_dev(div2);
    			if (if_block1) if_block1.d();
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block$1.name,
    		type: "if",
    		source: "(321:2) {#if !inspectBoolean}",
    		ctx
    	});

    	return block;
    }

    // (398:3) {#if privateRoomMembers && privateRoomMembers.length !== 0}
    function create_if_block_11(ctx) {
    	let div1;
    	let button;
    	let t1;
    	let div0;
    	let each_value_3 = /*privateRoomMembers*/ ctx[10];
    	validate_each_argument(each_value_3);
    	let each_blocks = [];

    	for (let i = 0; i < each_value_3.length; i += 1) {
    		each_blocks[i] = create_each_block_3(get_each_context_3(ctx, each_value_3, i));
    	}

    	const block = {
    		c: function create() {
    			div1 = element("div");
    			button = element("button");
    			button.textContent = "they wanna join";
    			t1 = space();
    			div0 = element("div");

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				each_blocks[i].c();
    			}

    			attr_dev(button, "class", "toggle-btn svelte-1b3tfzb");
    			add_location(button, file$2, 399, 5, 9430);
    			attr_dev(div0, "class", "room-list svelte-1b3tfzb");
    			add_location(div0, file$2, 400, 5, 9487);
    			attr_dev(div1, "class", "rooms-container svelte-1b3tfzb");
    			add_location(div1, file$2, 398, 4, 9395);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div1, anchor);
    			append_dev(div1, button);
    			append_dev(div1, t1);
    			append_dev(div1, div0);

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				if (each_blocks[i]) {
    					each_blocks[i].m(div0, null);
    				}
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*ban, privateRoomMembers, kick, accept*/ 13108224) {
    				each_value_3 = /*privateRoomMembers*/ ctx[10];
    				validate_each_argument(each_value_3);
    				let i;

    				for (i = 0; i < each_value_3.length; i += 1) {
    					const child_ctx = get_each_context_3(ctx, each_value_3, i);

    					if (each_blocks[i]) {
    						each_blocks[i].p(child_ctx, dirty);
    					} else {
    						each_blocks[i] = create_each_block_3(child_ctx);
    						each_blocks[i].c();
    						each_blocks[i].m(div0, null);
    					}
    				}

    				for (; i < each_blocks.length; i += 1) {
    					each_blocks[i].d(1);
    				}

    				each_blocks.length = each_value_3.length;
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div1);
    			destroy_each(each_blocks, detaching);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_11.name,
    		type: "if",
    		source: "(398:3) {#if privateRoomMembers && privateRoomMembers.length !== 0}",
    		ctx
    	});

    	return block;
    }

    // (402:6) {#each privateRoomMembers as member}
    function create_each_block_3(ctx) {
    	let div1;
    	let p;
    	let t0_value = /*member*/ ctx[63].name + "";
    	let t0;
    	let t1;
    	let div0;
    	let button0;
    	let t3;
    	let button1;
    	let t5;
    	let button2;
    	let t7;
    	let mounted;
    	let dispose;

    	function click_handler_6() {
    		return /*click_handler_6*/ ctx[38](/*member*/ ctx[63]);
    	}

    	function click_handler_7() {
    		return /*click_handler_7*/ ctx[39](/*member*/ ctx[63]);
    	}

    	function click_handler_8() {
    		return /*click_handler_8*/ ctx[40](/*member*/ ctx[63]);
    	}

    	const block = {
    		c: function create() {
    			div1 = element("div");
    			p = element("p");
    			t0 = text(t0_value);
    			t1 = space();
    			div0 = element("div");
    			button0 = element("button");
    			button0.textContent = "Accept";
    			t3 = space();
    			button1 = element("button");
    			button1.textContent = "Deny";
    			t5 = space();
    			button2 = element("button");
    			button2.textContent = "Ban";
    			t7 = space();
    			add_location(p, file$2, 403, 8, 9593);
    			add_location(button0, file$2, 405, 9, 9653);
    			add_location(button1, file$2, 406, 9, 9718);
    			add_location(button2, file$2, 407, 9, 9779);
    			attr_dev(div0, "class", "buttons");
    			add_location(div0, file$2, 404, 8, 9622);
    			attr_dev(div1, "class", "room-item svelte-1b3tfzb");
    			add_location(div1, file$2, 402, 7, 9561);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div1, anchor);
    			append_dev(div1, p);
    			append_dev(p, t0);
    			append_dev(div1, t1);
    			append_dev(div1, div0);
    			append_dev(div0, button0);
    			append_dev(div0, t3);
    			append_dev(div0, button1);
    			append_dev(div0, t5);
    			append_dev(div0, button2);
    			append_dev(div1, t7);

    			if (!mounted) {
    				dispose = [
    					listen_dev(button0, "click", click_handler_6, false, false, false, false),
    					listen_dev(button1, "click", click_handler_7, false, false, false, false),
    					listen_dev(button2, "click", click_handler_8, false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			if (dirty[0] & /*privateRoomMembers*/ 1024 && t0_value !== (t0_value = /*member*/ ctx[63].name + "")) set_data_dev(t0, t0_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div1);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_each_block_3.name,
    		type: "each",
    		source: "(402:6) {#each privateRoomMembers as member}",
    		ctx
    	});

    	return block;
    }

    // (432:9) {:else}
    function create_else_block_3(ctx) {
    	let t0;
    	let t1;
    	let button0;
    	let t3;
    	let button1;
    	let mounted;
    	let dispose;

    	function select_block_type_4(ctx, dirty) {
    		if (/*member*/ ctx[63].status === 2) return create_if_block_9;
    		if (/*member*/ ctx[63].status === 1) return create_if_block_10;
    	}

    	let current_block_type = select_block_type_4(ctx);
    	let if_block0 = current_block_type && current_block_type(ctx);

    	function select_block_type_5(ctx, dirty) {
    		if (/*member*/ ctx[63].status === 3) return create_if_block_8;
    		return create_else_block_4;
    	}

    	let current_block_type_1 = select_block_type_5(ctx);
    	let if_block1 = current_block_type_1(ctx);

    	function click_handler_14() {
    		return /*click_handler_14*/ ctx[46](/*member*/ ctx[63]);
    	}

    	function click_handler_15() {
    		return /*click_handler_15*/ ctx[47](/*member*/ ctx[63]);
    	}

    	const block = {
    		c: function create() {
    			if (if_block0) if_block0.c();
    			t0 = space();
    			if_block1.c();
    			t1 = space();
    			button0 = element("button");
    			button0.textContent = "kick";
    			t3 = space();
    			button1 = element("button");
    			button1.textContent = "Ban";
    			add_location(button0, file$2, 443, 10, 10853);
    			add_location(button1, file$2, 444, 10, 10915);
    		},
    		m: function mount(target, anchor) {
    			if (if_block0) if_block0.m(target, anchor);
    			insert_dev(target, t0, anchor);
    			if_block1.m(target, anchor);
    			insert_dev(target, t1, anchor);
    			insert_dev(target, button0, anchor);
    			insert_dev(target, t3, anchor);
    			insert_dev(target, button1, anchor);

    			if (!mounted) {
    				dispose = [
    					listen_dev(button0, "click", click_handler_14, false, false, false, false),
    					listen_dev(button1, "click", click_handler_15, false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;

    			if (current_block_type === (current_block_type = select_block_type_4(ctx)) && if_block0) {
    				if_block0.p(ctx, dirty);
    			} else {
    				if (if_block0) if_block0.d(1);
    				if_block0 = current_block_type && current_block_type(ctx);

    				if (if_block0) {
    					if_block0.c();
    					if_block0.m(t0.parentNode, t0);
    				}
    			}

    			if (current_block_type_1 === (current_block_type_1 = select_block_type_5(ctx)) && if_block1) {
    				if_block1.p(ctx, dirty);
    			} else {
    				if_block1.d(1);
    				if_block1 = current_block_type_1(ctx);

    				if (if_block1) {
    					if_block1.c();
    					if_block1.m(t1.parentNode, t1);
    				}
    			}
    		},
    		d: function destroy(detaching) {
    			if (if_block0) {
    				if_block0.d(detaching);
    			}

    			if (detaching) detach_dev(t0);
    			if_block1.d(detaching);
    			if (detaching) detach_dev(t1);
    			if (detaching) detach_dev(button0);
    			if (detaching) detach_dev(t3);
    			if (detaching) detach_dev(button1);
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block_3.name,
    		type: "else",
    		source: "(432:9) {:else}",
    		ctx
    	});

    	return block;
    }

    // (430:9) {#if member.status === 5}
    function create_if_block_7$1(ctx) {
    	let button;
    	let mounted;
    	let dispose;

    	function click_handler_9() {
    		return /*click_handler_9*/ ctx[41](/*member*/ ctx[63]);
    	}

    	const block = {
    		c: function create() {
    			button = element("button");
    			button.textContent = "unban";
    			add_location(button, file$2, 430, 10, 10342);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, button, anchor);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_9, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_7$1.name,
    		type: "if",
    		source: "(430:9) {#if member.status === 5}",
    		ctx
    	});

    	return block;
    }

    // (435:40) 
    function create_if_block_10(ctx) {
    	let button;
    	let mounted;
    	let dispose;

    	function click_handler_11() {
    		return /*click_handler_11*/ ctx[43](/*member*/ ctx[63]);
    	}

    	const block = {
    		c: function create() {
    			button = element("button");
    			button.textContent = "Demote";
    			add_location(button, file$2, 435, 11, 10569);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, button, anchor);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_11, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_10.name,
    		type: "if",
    		source: "(435:40) ",
    		ctx
    	});

    	return block;
    }

    // (433:10) {#if member.status === 2}
    function create_if_block_9(ctx) {
    	let button;
    	let mounted;
    	let dispose;

    	function click_handler_10() {
    		return /*click_handler_10*/ ctx[42](/*member*/ ctx[63]);
    	}

    	const block = {
    		c: function create() {
    			button = element("button");
    			button.textContent = "Promote";
    			add_location(button, file$2, 433, 11, 10459);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, button, anchor);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_10, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_9.name,
    		type: "if",
    		source: "(433:10) {#if member.status === 2}",
    		ctx
    	});

    	return block;
    }

    // (441:10) {:else}
    function create_else_block_4(ctx) {
    	let button;
    	let mounted;
    	let dispose;

    	function click_handler_13() {
    		return /*click_handler_13*/ ctx[45](/*member*/ ctx[63]);
    	}

    	const block = {
    		c: function create() {
    			button = element("button");
    			button.textContent = "mute";
    			add_location(button, file$2, 441, 11, 10775);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, button, anchor);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_13, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block_4.name,
    		type: "else",
    		source: "(441:10) {:else}",
    		ctx
    	});

    	return block;
    }

    // (439:10) {#if member.status === 3}
    function create_if_block_8(ctx) {
    	let button;
    	let mounted;
    	let dispose;

    	function click_handler_12() {
    		return /*click_handler_12*/ ctx[44](/*member*/ ctx[63]);
    	}

    	const block = {
    		c: function create() {
    			button = element("button");
    			button.textContent = "unmute";
    			add_location(button, file$2, 439, 11, 10690);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, button, anchor);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_12, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_8.name,
    		type: "if",
    		source: "(439:10) {#if member.status === 3}",
    		ctx
    	});

    	return block;
    }

    // (422:6) {#each roomMembers as member}
    function create_each_block_2(ctx) {
    	let div2;
    	let div0;
    	let p0;
    	let t0_value = /*member*/ ctx[63].name + "";
    	let t0;
    	let t1;
    	let p1;
    	let t2;
    	let t3_value = /*memberStatusLabels*/ ctx[26][/*member*/ ctx[63].status] + "";
    	let t3;
    	let t4;
    	let t5;
    	let div1;
    	let t6;

    	function select_block_type_3(ctx, dirty) {
    		if (/*member*/ ctx[63].status === 5) return create_if_block_7$1;
    		return create_else_block_3;
    	}

    	let current_block_type = select_block_type_3(ctx);
    	let if_block = current_block_type(ctx);

    	const block = {
    		c: function create() {
    			div2 = element("div");
    			div0 = element("div");
    			p0 = element("p");
    			t0 = text(t0_value);
    			t1 = space();
    			p1 = element("p");
    			t2 = text("[");
    			t3 = text(t3_value);
    			t4 = text("]");
    			t5 = space();
    			div1 = element("div");
    			if_block.c();
    			t6 = space();
    			add_location(p0, file$2, 424, 9, 10176);
    			add_location(p1, file$2, 425, 9, 10206);
    			add_location(div0, file$2, 423, 8, 10161);
    			attr_dev(div1, "class", "buttons");
    			add_location(div1, file$2, 428, 8, 10275);
    			attr_dev(div2, "class", "room-item svelte-1b3tfzb");
    			add_location(div2, file$2, 422, 7, 10129);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div2, anchor);
    			append_dev(div2, div0);
    			append_dev(div0, p0);
    			append_dev(p0, t0);
    			append_dev(div0, t1);
    			append_dev(div0, p1);
    			append_dev(p1, t2);
    			append_dev(p1, t3);
    			append_dev(p1, t4);
    			append_dev(div2, t5);
    			append_dev(div2, div1);
    			if_block.m(div1, null);
    			append_dev(div2, t6);
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*roomMembers*/ 2048 && t0_value !== (t0_value = /*member*/ ctx[63].name + "")) set_data_dev(t0, t0_value);
    			if (dirty[0] & /*roomMembers*/ 2048 && t3_value !== (t3_value = /*memberStatusLabels*/ ctx[26][/*member*/ ctx[63].status] + "")) set_data_dev(t3, t3_value);

    			if (current_block_type === (current_block_type = select_block_type_3(ctx)) && if_block) {
    				if_block.p(ctx, dirty);
    			} else {
    				if_block.d(1);
    				if_block = current_block_type(ctx);

    				if (if_block) {
    					if_block.c();
    					if_block.m(div1, null);
    				}
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div2);
    			if_block.d();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_each_block_2.name,
    		type: "each",
    		source: "(422:6) {#each roomMembers as member}",
    		ctx
    	});

    	return block;
    }

    // (322:3) {#if ownedRoom && ownedRoom.length > 0}
    function create_if_block_5$1(ctx) {
    	let div1;
    	let button;
    	let t1;
    	let div0;
    	let each_value_1 = /*ownedRoom*/ ctx[6];
    	validate_each_argument(each_value_1);
    	let each_blocks = [];

    	for (let i = 0; i < each_value_1.length; i += 1) {
    		each_blocks[i] = create_each_block_1(get_each_context_1(ctx, each_value_1, i));
    	}

    	const block = {
    		c: function create() {
    			div1 = element("div");
    			button = element("button");
    			button.textContent = "Your Rooms";
    			t1 = space();
    			div0 = element("div");

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				each_blocks[i].c();
    			}

    			attr_dev(button, "class", "toggle-btn svelte-1b3tfzb");
    			add_location(button, file$2, 323, 5, 7123);
    			attr_dev(div0, "class", "room-list svelte-1b3tfzb");
    			add_location(div0, file$2, 324, 5, 7175);
    			attr_dev(div1, "class", "rooms-container svelte-1b3tfzb");
    			add_location(div1, file$2, 322, 4, 7088);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div1, anchor);
    			append_dev(div1, button);
    			append_dev(div1, t1);
    			append_dev(div1, div0);

    			for (let i = 0; i < each_blocks.length; i += 1) {
    				if (each_blocks[i]) {
    					each_blocks[i].m(div0, null);
    				}
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*switchDisplay, ownedRoom*/ 262208) {
    				each_value_1 = /*ownedRoom*/ ctx[6];
    				validate_each_argument(each_value_1);
    				let i;

    				for (i = 0; i < each_value_1.length; i += 1) {
    					const child_ctx = get_each_context_1(ctx, each_value_1, i);

    					if (each_blocks[i]) {
    						each_blocks[i].p(child_ctx, dirty);
    					} else {
    						each_blocks[i] = create_each_block_1(child_ctx);
    						each_blocks[i].c();
    						each_blocks[i].m(div0, null);
    					}
    				}

    				for (; i < each_blocks.length; i += 1) {
    					each_blocks[i].d(1);
    				}

    				each_blocks.length = each_value_1.length;
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div1);
    			destroy_each(each_blocks, detaching);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_5$1.name,
    		type: "if",
    		source: "(322:3) {#if ownedRoom && ownedRoom.length > 0}",
    		ctx
    	});

    	return block;
    }

    // (331:8) {:else}
    function create_else_block_1(ctx) {
    	let p;

    	const block = {
    		c: function create() {
    			p = element("p");
    			p.textContent = "[admin]";
    			add_location(p, file$2, 331, 9, 7357);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block_1.name,
    		type: "else",
    		source: "(331:8) {:else}",
    		ctx
    	});

    	return block;
    }

    // (329:8) {#if roomList.status === 0}
    function create_if_block_6$1(ctx) {
    	let p;

    	const block = {
    		c: function create() {
    			p = element("p");
    			p.textContent = "[owner]";
    			add_location(p, file$2, 329, 9, 7317);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, p, anchor);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(p);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_6$1.name,
    		type: "if",
    		source: "(329:8) {#if roomList.status === 0}",
    		ctx
    	});

    	return block;
    }

    // (327:6) {#each ownedRoom as roomList}
    function create_each_block_1(ctx) {
    	let div;
    	let t0;
    	let h3;
    	let t1_value = /*roomList*/ ctx[60].room.name + "";
    	let t1;
    	let t2;
    	let button;
    	let t4;
    	let mounted;
    	let dispose;

    	function select_block_type_1(ctx, dirty) {
    		if (/*roomList*/ ctx[60].status === 0) return create_if_block_6$1;
    		return create_else_block_1;
    	}

    	let current_block_type = select_block_type_1(ctx);
    	let if_block = current_block_type(ctx);

    	function click_handler_1() {
    		return /*click_handler_1*/ ctx[30](/*roomList*/ ctx[60]);
    	}

    	const block = {
    		c: function create() {
    			div = element("div");
    			if_block.c();
    			t0 = space();
    			h3 = element("h3");
    			t1 = text(t1_value);
    			t2 = space();
    			button = element("button");
    			button.textContent = "Inspect";
    			t4 = space();
    			attr_dev(h3, "class", "svelte-1b3tfzb");
    			add_location(h3, file$2, 334, 8, 7403);
    			attr_dev(button, "class", "join-button svelte-1b3tfzb");
    			add_location(button, file$2, 335, 8, 7441);
    			attr_dev(div, "class", "room-item svelte-1b3tfzb");
    			add_location(div, file$2, 327, 7, 7248);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div, anchor);
    			if_block.m(div, null);
    			append_dev(div, t0);
    			append_dev(div, h3);
    			append_dev(h3, t1);
    			append_dev(div, t2);
    			append_dev(div, button);
    			append_dev(div, t4);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_1, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;

    			if (current_block_type !== (current_block_type = select_block_type_1(ctx))) {
    				if_block.d(1);
    				if_block = current_block_type(ctx);

    				if (if_block) {
    					if_block.c();
    					if_block.m(div, t0);
    				}
    			}

    			if (dirty[0] & /*ownedRoom*/ 64 && t1_value !== (t1_value = /*roomList*/ ctx[60].room.name + "")) set_data_dev(t1, t1_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div);
    			if_block.d();
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_each_block_1.name,
    		type: "each",
    		source: "(327:6) {#each ownedRoom as roomList}",
    		ctx
    	});

    	return block;
    }

    // (359:7) {:else}
    function create_else_block(ctx) {
    	let h3;
    	let t0;
    	let t1_value = /*room*/ ctx[57].name + "";
    	let t1;
    	let t2;
    	let button;
    	let mounted;
    	let dispose;

    	function click_handler_4() {
    		return /*click_handler_4*/ ctx[33](/*room*/ ctx[57]);
    	}

    	const block = {
    		c: function create() {
    			h3 = element("h3");
    			t0 = text("✅ ");
    			t1 = text(t1_value);
    			t2 = space();
    			button = element("button");
    			button.textContent = "Join";
    			attr_dev(h3, "class", "svelte-1b3tfzb");
    			add_location(h3, file$2, 359, 8, 8157);
    			attr_dev(button, "class", "join-button svelte-1b3tfzb");
    			add_location(button, file$2, 360, 8, 8188);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, h3, anchor);
    			append_dev(h3, t0);
    			append_dev(h3, t1);
    			insert_dev(target, t2, anchor);
    			insert_dev(target, button, anchor);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_4, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			if (dirty[0] & /*rooms*/ 2 && t1_value !== (t1_value = /*room*/ ctx[57].name + "")) set_data_dev(t1, t1_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(h3);
    			if (detaching) detach_dev(t2);
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_else_block.name,
    		type: "else",
    		source: "(359:7) {:else}",
    		ctx
    	});

    	return block;
    }

    // (356:32) 
    function create_if_block_4$1(ctx) {
    	let h3;
    	let t0;
    	let t1_value = /*room*/ ctx[57].name + "";
    	let t1;
    	let t2;
    	let button;
    	let mounted;
    	let dispose;

    	function click_handler_3() {
    		return /*click_handler_3*/ ctx[32](/*room*/ ctx[57]);
    	}

    	const block = {
    		c: function create() {
    			h3 = element("h3");
    			t0 = text("🔒 ");
    			t1 = text(t1_value);
    			t2 = space();
    			button = element("button");
    			button.textContent = "Ask to join";
    			attr_dev(h3, "class", "svelte-1b3tfzb");
    			add_location(h3, file$2, 356, 8, 8025);
    			attr_dev(button, "class", "join-button svelte-1b3tfzb");
    			add_location(button, file$2, 357, 8, 8057);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, h3, anchor);
    			append_dev(h3, t0);
    			append_dev(h3, t1);
    			insert_dev(target, t2, anchor);
    			insert_dev(target, button, anchor);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_3, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			if (dirty[0] & /*rooms*/ 2 && t1_value !== (t1_value = /*room*/ ctx[57].name + "")) set_data_dev(t1, t1_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(h3);
    			if (detaching) detach_dev(t2);
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_4$1.name,
    		type: "if",
    		source: "(356:32) ",
    		ctx
    	});

    	return block;
    }

    // (353:7) {#if room.secu == 1}
    function create_if_block_3$1(ctx) {
    	let h3;
    	let t0;
    	let t1_value = /*room*/ ctx[57].name + "";
    	let t1;
    	let t2;
    	let button;
    	let mounted;
    	let dispose;

    	function click_handler_2() {
    		return /*click_handler_2*/ ctx[31](/*room*/ ctx[57]);
    	}

    	const block = {
    		c: function create() {
    			h3 = element("h3");
    			t0 = text("❌ ");
    			t1 = text(t1_value);
    			t2 = space();
    			button = element("button");
    			button.textContent = "Protected";
    			attr_dev(h3, "class", "svelte-1b3tfzb");
    			add_location(h3, file$2, 353, 8, 7868);
    			attr_dev(button, "class", "join-button svelte-1b3tfzb");
    			add_location(button, file$2, 354, 8, 7899);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, h3, anchor);
    			append_dev(h3, t0);
    			append_dev(h3, t1);
    			insert_dev(target, t2, anchor);
    			insert_dev(target, button, anchor);

    			if (!mounted) {
    				dispose = listen_dev(button, "click", click_handler_2, false, false, false, false);
    				mounted = true;
    			}
    		},
    		p: function update(new_ctx, dirty) {
    			ctx = new_ctx;
    			if (dirty[0] & /*rooms*/ 2 && t1_value !== (t1_value = /*room*/ ctx[57].name + "")) set_data_dev(t1, t1_value);
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(h3);
    			if (detaching) detach_dev(t2);
    			if (detaching) detach_dev(button);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_3$1.name,
    		type: "if",
    		source: "(353:7) {#if room.secu == 1}",
    		ctx
    	});

    	return block;
    }

    // (351:5) {#each rooms as room}
    function create_each_block(ctx) {
    	let div;
    	let t;

    	function select_block_type_2(ctx, dirty) {
    		if (/*room*/ ctx[57].secu == 1) return create_if_block_3$1;
    		if (/*room*/ ctx[57].secu == 2) return create_if_block_4$1;
    		return create_else_block;
    	}

    	let current_block_type = select_block_type_2(ctx);
    	let if_block = current_block_type(ctx);

    	const block = {
    		c: function create() {
    			div = element("div");
    			if_block.c();
    			t = space();
    			attr_dev(div, "class", "room-item svelte-1b3tfzb");
    			add_location(div, file$2, 351, 6, 7808);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div, anchor);
    			if_block.m(div, null);
    			append_dev(div, t);
    		},
    		p: function update(ctx, dirty) {
    			if (current_block_type === (current_block_type = select_block_type_2(ctx)) && if_block) {
    				if_block.p(ctx, dirty);
    			} else {
    				if_block.d(1);
    				if_block = current_block_type(ctx);

    				if (if_block) {
    					if_block.c();
    					if_block.m(div, t);
    				}
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div);
    			if_block.d();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_each_block.name,
    		type: "each",
    		source: "(351:5) {#each rooms as room}",
    		ctx
    	});

    	return block;
    }

    // (370:4) {#if isFormVisible}
    function create_if_block_1$1(ctx) {
    	let form;
    	let label0;
    	let t1;
    	let input;
    	let t2;
    	let br0;
    	let t3;
    	let label1;
    	let t5;
    	let select;
    	let option0;
    	let option1;
    	let option2;
    	let t9;
    	let t10;
    	let br1;
    	let t11;
    	let button;
    	let mounted;
    	let dispose;
    	let if_block = /*roomType*/ ctx[4] === "protected" && create_if_block_2$1(ctx);

    	const block = {
    		c: function create() {
    			form = element("form");
    			label0 = element("label");
    			label0.textContent = "Room Name:";
    			t1 = space();
    			input = element("input");
    			t2 = space();
    			br0 = element("br");
    			t3 = space();
    			label1 = element("label");
    			label1.textContent = "Room Type:";
    			t5 = space();
    			select = element("select");
    			option0 = element("option");
    			option0.textContent = "Public";
    			option1 = element("option");
    			option1.textContent = "Private";
    			option2 = element("option");
    			option2.textContent = "Protected";
    			t9 = space();
    			if (if_block) if_block.c();
    			t10 = space();
    			br1 = element("br");
    			t11 = space();
    			button = element("button");
    			button.textContent = "Create Room";
    			attr_dev(label0, "for", "room-name");
    			add_location(label0, file$2, 371, 6, 8494);
    			attr_dev(input, "type", "text");
    			attr_dev(input, "id", "room-name");
    			add_location(input, file$2, 372, 6, 8542);
    			add_location(br0, file$2, 373, 6, 8607);
    			attr_dev(label1, "for", "room-type");
    			add_location(label1, file$2, 374, 6, 8620);
    			option0.__value = "public";
    			option0.value = option0.__value;
    			add_location(option0, file$2, 376, 7, 8721);
    			option1.__value = "private";
    			option1.value = option1.__value;
    			add_location(option1, file$2, 377, 7, 8767);
    			option2.__value = "protected";
    			option2.value = option2.__value;
    			add_location(option2, file$2, 378, 7, 8815);
    			attr_dev(select, "id", "room-type");
    			if (/*roomType*/ ctx[4] === void 0) add_render_callback(() => /*select_change_handler*/ ctx[35].call(select));
    			add_location(select, file$2, 375, 6, 8668);
    			add_location(br1, file$2, 385, 6, 9061);
    			attr_dev(button, "type", "submit");
    			add_location(button, file$2, 386, 6, 9074);
    			add_location(form, file$2, 370, 5, 8456);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, form, anchor);
    			append_dev(form, label0);
    			append_dev(form, t1);
    			append_dev(form, input);
    			set_input_value(input, /*roomName*/ ctx[3]);
    			append_dev(form, t2);
    			append_dev(form, br0);
    			append_dev(form, t3);
    			append_dev(form, label1);
    			append_dev(form, t5);
    			append_dev(form, select);
    			append_dev(select, option0);
    			append_dev(select, option1);
    			append_dev(select, option2);
    			select_option(select, /*roomType*/ ctx[4], true);
    			append_dev(form, t9);
    			if (if_block) if_block.m(form, null);
    			append_dev(form, t10);
    			append_dev(form, br1);
    			append_dev(form, t11);
    			append_dev(form, button);

    			if (!mounted) {
    				dispose = [
    					listen_dev(input, "input", /*input_input_handler*/ ctx[34]),
    					listen_dev(select, "change", /*select_change_handler*/ ctx[35]),
    					listen_dev(form, "submit", /*handleSubmit*/ ctx[14], false, false, false, false)
    				];

    				mounted = true;
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*roomName*/ 8 && input.value !== /*roomName*/ ctx[3]) {
    				set_input_value(input, /*roomName*/ ctx[3]);
    			}

    			if (dirty[0] & /*roomType*/ 16) {
    				select_option(select, /*roomType*/ ctx[4]);
    			}

    			if (/*roomType*/ ctx[4] === "protected") {
    				if (if_block) {
    					if_block.p(ctx, dirty);
    				} else {
    					if_block = create_if_block_2$1(ctx);
    					if_block.c();
    					if_block.m(form, t10);
    				}
    			} else if (if_block) {
    				if_block.d(1);
    				if_block = null;
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(form);
    			if (if_block) if_block.d();
    			mounted = false;
    			run_all(dispose);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_1$1.name,
    		type: "if",
    		source: "(370:4) {#if isFormVisible}",
    		ctx
    	});

    	return block;
    }

    // (381:6) {#if roomType === "protected"}
    function create_if_block_2$1(ctx) {
    	let br;
    	let t0;
    	let label;
    	let t2;
    	let input;
    	let mounted;
    	let dispose;

    	const block = {
    		c: function create() {
    			br = element("br");
    			t0 = space();
    			label = element("label");
    			label.textContent = "Password:";
    			t2 = space();
    			input = element("input");
    			add_location(br, file$2, 381, 7, 8920);
    			attr_dev(label, "for", "password");
    			add_location(label, file$2, 382, 7, 8934);
    			attr_dev(input, "type", "password");
    			attr_dev(input, "id", "password");
    			add_location(input, file$2, 383, 7, 8981);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, br, anchor);
    			insert_dev(target, t0, anchor);
    			insert_dev(target, label, anchor);
    			insert_dev(target, t2, anchor);
    			insert_dev(target, input, anchor);
    			set_input_value(input, /*password*/ ctx[5]);

    			if (!mounted) {
    				dispose = listen_dev(input, "input", /*input_input_handler_1*/ ctx[36]);
    				mounted = true;
    			}
    		},
    		p: function update(ctx, dirty) {
    			if (dirty[0] & /*password*/ 32 && input.value !== /*password*/ ctx[5]) {
    				set_input_value(input, /*password*/ ctx[5]);
    			}
    		},
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(br);
    			if (detaching) detach_dev(t0);
    			if (detaching) detach_dev(label);
    			if (detaching) detach_dev(t2);
    			if (detaching) detach_dev(input);
    			mounted = false;
    			dispose();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_2$1.name,
    		type: "if",
    		source: "(381:6) {#if roomType === \\\"protected\\\"}",
    		ctx
    	});

    	return block;
    }

    function create_fragment$2(ctx) {
    	let t;
    	let div;
    	let main;
    	let current;
    	let if_block0 = /*delTab*/ ctx[12] && create_if_block_12(ctx);

    	function select_block_type(ctx, dirty) {
    		if (!/*inspectBoolean*/ ctx[7]) return create_if_block$1;
    		return create_else_block_2;
    	}

    	let current_block_type = select_block_type(ctx);
    	let if_block1 = current_block_type(ctx);

    	const block = {
    		c: function create() {
    			if (if_block0) if_block0.c();
    			t = space();
    			div = element("div");
    			main = element("main");
    			if_block1.c();
    			attr_dev(main, "class", "container svelte-1b3tfzb");
    			add_location(main, file$2, 318, 1, 6991);
    			attr_dev(div, "class", "main_body");
    			add_location(div, file$2, 317, 0, 6966);
    		},
    		l: function claim(nodes) {
    			throw new Error_1$1("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			if (if_block0) if_block0.m(target, anchor);
    			insert_dev(target, t, anchor);
    			insert_dev(target, div, anchor);
    			append_dev(div, main);
    			if_block1.m(main, null);
    			current = true;
    		},
    		p: function update(ctx, dirty) {
    			if (/*delTab*/ ctx[12]) {
    				if (if_block0) {
    					if_block0.p(ctx, dirty);

    					if (dirty[0] & /*delTab*/ 4096) {
    						transition_in(if_block0, 1);
    					}
    				} else {
    					if_block0 = create_if_block_12(ctx);
    					if_block0.c();
    					transition_in(if_block0, 1);
    					if_block0.m(t.parentNode, t);
    				}
    			} else if (if_block0) {
    				group_outros();

    				transition_out(if_block0, 1, 1, () => {
    					if_block0 = null;
    				});

    				check_outros();
    			}

    			if (current_block_type === (current_block_type = select_block_type(ctx)) && if_block1) {
    				if_block1.p(ctx, dirty);
    			} else {
    				if_block1.d(1);
    				if_block1 = current_block_type(ctx);

    				if (if_block1) {
    					if_block1.c();
    					if_block1.m(main, null);
    				}
    			}
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(if_block0);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(if_block0);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			if (if_block0) if_block0.d(detaching);
    			if (detaching) detach_dev(t);
    			if (detaching) detach_dev(div);
    			if_block1.d();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$2.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$2($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('Rooms', slots, []);
    	let { data } = $$props;
    	let rooms = [];
    	let isFormVisible = false;
    	let roomName = '';
    	let roomType = 'public';
    	let password = '';

    	const toggleForm = () => {
    		$$invalidate(2, isFormVisible = !isFormVisible);
    	};

    	//-----------CREATE----ROOM---------------------------------//
    	const handleSubmit = async event => {
    		event.preventDefault();
    		console.log('Creating room:', roomName, 'of type', roomType);

    		if (roomType === 'protected') {
    			console.log('Password:', password);
    		}

    		// ici je fais api call  au back
    		const response = await fetch(`http://${hostname}:3000/chat`, {
    			method: 'POST',
    			headers: { 'Content-Type': 'application/json' },
    			body: JSON.stringify({
    				roomName,
    				roomType,
    				password,
    				iddata: data.id
    			})
    		});

    		if (response.ok) {
    			console.log('Room created successfully');
    		} else {
    			console.error('Failed to create room'); // handle success -> make sure that room is added to the list updates etc
    		} // handle error

    		// Reset les valeurs du formulaure
    		$$invalidate(3, roomName = '');

    		$$invalidate(4, roomType = 'public');
    		$$invalidate(5, password = '');
    		toggleForm();
    		fetchRooms();
    		fetchOwnedRoom();
    	};

    	//-------------------------LIST----ROOM-----------------------------//
    	const fetchRooms = async () => {
    		const response = await fetch(`http://${hostname}:3000/rooms/valideRooms/${data.id}`);

    		if (response.ok) {
    			$$invalidate(1, rooms = await response.json());
    		} else {
    			console.error('Failed to fetch rooms');
    		}
    	};

    	//----------------------------ONMOUNT----------------------------//
    	onMount(fetchRooms);

    	onMount(fetchOwnedRoom);

    	//-------------------------JOIN--PRIVATE----------------------------//
    	const handlePasswordInput = async (room, password) => {
    		const response = await fetch(`http://${hostname}:3000/chat/verify-password`, {
    			method: 'POST',
    			headers: { 'Content-Type': 'application/json' },
    			body: JSON.stringify({
    				roomId: room.id,
    				password,
    				iddata: data.id
    			})
    		});

    		if (response.ok) {
    			console.log('Password is correct');
    		} else {
    			console.error('Incorrect password or error');
    		}
    	};

    	const askForPassword = room => {
    		const password = prompt('Enter the password:');

    		if (password !== null) {
    			handlePasswordInput(room, password);
    		}
    	};

    	//---------------------------JOIN----------NORMAL------------------//
    	const join = async room => {
    		const response = await fetch(`http://${hostname}:3000/rooms/join/${room.id}/${data.id}`, { method: 'POST' });

    		if (response.ok) {
    			console.log('Joined room:', room.name);
    		} else {
    			console.error('Failed to join room:', room.name);
    		}

    		fetchRooms();
    	};

    	//---------------------------OwnedRoom----------LIST------------------//
    	let ownedRoom = [];

    	async function fetchOwnedRoom() {
    		try {
    			const response = await fetch(`http://${hostname}:3000/rooms/${data.id}`);
    			if (response.ok) $$invalidate(6, ownedRoom = await response.json()); else $$invalidate(6, ownedRoom = []);
    			console.log(ownedRoom);
    		} catch(error) {
    			console.error(error);
    		}
    	}

    	let inspectBoolean = false;

    	function inspectToggle() {
    		$$invalidate(7, inspectBoolean = !inspectBoolean);

    		if (!inspectBoolean) {
    			$$invalidate(8, choosenRoom = null);
    			$$invalidate(9, choosenRoomId = null);
    			$$invalidate(10, privateRoomMembers = null);
    			$$invalidate(11, roomMembers = []);
    		}
    	}

    	let choosenRoom;
    	let choosenRoomId;
    	let status;

    	async function switchDisplay(room, roomStatus) {
    		$$invalidate(8, choosenRoom = room.name);
    		$$invalidate(9, choosenRoomId = room.id);
    		status = roomStatus;
    		fetchprivateRoomMembers();
    		fetchAllRoomMembers();
    		inspectToggle();
    	}

    	let privateRoomMembers = null;

    	async function fetchprivateRoomMembers() {
    		try {
    			const response = await fetch(`http://${hostname}:3000/rooms/privateRoomMember/${choosenRoomId}`);
    			if (response.ok) $$invalidate(10, privateRoomMembers = await response.json()); else $$invalidate(10, privateRoomMembers = null);
    		} catch(error) {
    			console.error(error);
    		}
    	}

    	let roomMembers = [];

    	async function fetchAllRoomMembers() {
    		let url;
    		if (status === 0) url = `http://${hostname}:3000/rooms/allRoomMember/${choosenRoomId}/${data.id}`; else url = `http://${hostname}:3000/rooms/allRoomMemberForAdmins/${choosenRoomId}/${data.id}`;

    		try {
    			const response = await fetch(url);
    			if (response.ok) $$invalidate(11, roomMembers = await response.json()); else $$invalidate(11, roomMembers = null);
    		} catch(error) {
    			console.error(error);
    		}
    	}

    	async function updateClientStatus(roomId, clientId, status) {
    		try {
    			const response = await fetch(`http://${hostname}:3000/rooms/updateStatus/${roomId}/${clientId}/${status}`, { method: 'POST' });

    			if (response.ok) {
    				console.log('Status updated successfully');
    			} else {
    				console.error('Failed to update status');
    			}
    		} catch(error) {
    			console.error('An error occurred', error);
    		}
    	}

    	async function accept(client) {
    		try {
    			const response = await fetch(`http://${hostname}:3000/rooms/acceptNewMember/${choosenRoomId}/${client.id}`, { method: 'POST' });

    			if (response.ok) {
    				console.log('New member accepted');
    			} else {
    				const errorText = await response.text(); // Mettez à jour votre état ou effectuez toute autre action nécessaire ici
    				throw new Error(errorText);
    			}
    		} catch(error) {
    			console.error(error);
    		}

    		await fetchAllRoomMembers();
    		await fetchprivateRoomMembers();
    	}

    	async function promote(client) {
    		await updateClientStatus(choosenRoomId, client.id, 1);
    		await fetchAllRoomMembers();
    	}

    	async function demote(client) {
    		await updateClientStatus(choosenRoomId, client.id, 2);
    		await fetchAllRoomMembers();
    	}

    	async function ban(client) {
    		await updateClientStatus(choosenRoomId, client.id, 5);
    		await fetchAllRoomMembers();
    		await fetchprivateRoomMembers();
    	}

    	async function kick(client) {
    		try {
    			const response = await fetch(`http://${hostname}:3000/rooms/kick/${choosenRoomId}/${client.id}`, { method: 'POST' });

    			if (response.ok) console.log('client kicked'); else {
    				const errorText = await response.text();
    				throw new Error(errorText);
    			}
    		} catch(error) {
    			throw new Error(error.message);
    		}

    		await fetchAllRoomMembers();
    		await fetchprivateRoomMembers();
    	}

    	async function mute(client) {
    		await updateClientStatus(choosenRoomId, client.id, 3);
    		await fetchAllRoomMembers();
    	}

    	async function unmute(client) {
    		await updateClientStatus(choosenRoomId, client.id, 2);
    		await fetchAllRoomMembers();
    	}

    	const memberStatusLabels = {
    		1: 'admin',
    		2: 'member',
    		3: 'muted',
    		4: 'kicked',
    		5: 'banned',
    		6: 'pendant'
    	};

    	let delTab = null;

    	function toggleDel(source) {
    		$$invalidate(12, delTab = source);
    	}

    	function delReturn() {
    		$$invalidate(12, delTab = null);
    		fetchOwnedRoom();
    		fetchRooms();
    		inspectToggle();
    	}

    	$$self.$$.on_mount.push(function () {
    		if (data === undefined && !('data' in $$props || $$self.$$.bound[$$self.$$.props['data']])) {
    			console_1$1.warn("<Rooms> was created without expected prop 'data'");
    		}
    	});

    	const writable_props = ['data'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console_1$1.warn(`<Rooms> was created with unknown prop '${key}'`);
    	});

    	const click_handler = () => toggleDel(null);
    	const click_handler_1 = roomList => switchDisplay(roomList.room, roomList.status);
    	const click_handler_2 = room => askForPassword(room);
    	const click_handler_3 = room => join(room);
    	const click_handler_4 = room => join(room);

    	function input_input_handler() {
    		roomName = this.value;
    		$$invalidate(3, roomName);
    	}

    	function select_change_handler() {
    		roomType = select_value(this);
    		$$invalidate(4, roomType);
    	}

    	function input_input_handler_1() {
    		password = this.value;
    		$$invalidate(5, password);
    	}

    	const click_handler_5 = () => inspectToggle();
    	const click_handler_6 = member => accept(member);
    	const click_handler_7 = member => kick(member);
    	const click_handler_8 = member => ban(member);
    	const click_handler_9 = member => kick(member);
    	const click_handler_10 = member => promote(member);
    	const click_handler_11 = member => demote(member);
    	const click_handler_12 = member => unmute(member);
    	const click_handler_13 = member => mute(member);
    	const click_handler_14 = member => kick(member);
    	const click_handler_15 = member => ban(member);
    	const click_handler_16 = () => toggleDel('del');
    	const click_handler_17 = () => toggleDel('res');

    	$$self.$$set = $$props => {
    		if ('data' in $$props) $$invalidate(0, data = $$props.data);
    	};

    	$$self.$capture_state = () => ({
    		onMount,
    		hostname,
    		DelModal: Delete_resign,
    		data,
    		rooms,
    		isFormVisible,
    		roomName,
    		roomType,
    		password,
    		toggleForm,
    		handleSubmit,
    		fetchRooms,
    		handlePasswordInput,
    		askForPassword,
    		join,
    		ownedRoom,
    		fetchOwnedRoom,
    		inspectBoolean,
    		inspectToggle,
    		choosenRoom,
    		choosenRoomId,
    		status,
    		switchDisplay,
    		privateRoomMembers,
    		fetchprivateRoomMembers,
    		roomMembers,
    		fetchAllRoomMembers,
    		updateClientStatus,
    		accept,
    		promote,
    		demote,
    		ban,
    		kick,
    		mute,
    		unmute,
    		memberStatusLabels,
    		delTab,
    		toggleDel,
    		delReturn
    	});

    	$$self.$inject_state = $$props => {
    		if ('data' in $$props) $$invalidate(0, data = $$props.data);
    		if ('rooms' in $$props) $$invalidate(1, rooms = $$props.rooms);
    		if ('isFormVisible' in $$props) $$invalidate(2, isFormVisible = $$props.isFormVisible);
    		if ('roomName' in $$props) $$invalidate(3, roomName = $$props.roomName);
    		if ('roomType' in $$props) $$invalidate(4, roomType = $$props.roomType);
    		if ('password' in $$props) $$invalidate(5, password = $$props.password);
    		if ('ownedRoom' in $$props) $$invalidate(6, ownedRoom = $$props.ownedRoom);
    		if ('inspectBoolean' in $$props) $$invalidate(7, inspectBoolean = $$props.inspectBoolean);
    		if ('choosenRoom' in $$props) $$invalidate(8, choosenRoom = $$props.choosenRoom);
    		if ('choosenRoomId' in $$props) $$invalidate(9, choosenRoomId = $$props.choosenRoomId);
    		if ('status' in $$props) status = $$props.status;
    		if ('privateRoomMembers' in $$props) $$invalidate(10, privateRoomMembers = $$props.privateRoomMembers);
    		if ('roomMembers' in $$props) $$invalidate(11, roomMembers = $$props.roomMembers);
    		if ('delTab' in $$props) $$invalidate(12, delTab = $$props.delTab);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [
    		data,
    		rooms,
    		isFormVisible,
    		roomName,
    		roomType,
    		password,
    		ownedRoom,
    		inspectBoolean,
    		choosenRoom,
    		choosenRoomId,
    		privateRoomMembers,
    		roomMembers,
    		delTab,
    		toggleForm,
    		handleSubmit,
    		askForPassword,
    		join,
    		inspectToggle,
    		switchDisplay,
    		accept,
    		promote,
    		demote,
    		ban,
    		kick,
    		mute,
    		unmute,
    		memberStatusLabels,
    		toggleDel,
    		delReturn,
    		click_handler,
    		click_handler_1,
    		click_handler_2,
    		click_handler_3,
    		click_handler_4,
    		input_input_handler,
    		select_change_handler,
    		input_input_handler_1,
    		click_handler_5,
    		click_handler_6,
    		click_handler_7,
    		click_handler_8,
    		click_handler_9,
    		click_handler_10,
    		click_handler_11,
    		click_handler_12,
    		click_handler_13,
    		click_handler_14,
    		click_handler_15,
    		click_handler_16,
    		click_handler_17
    	];
    }

    class Rooms extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$2, create_fragment$2, safe_not_equal, { data: 0 }, null, [-1, -1, -1]);

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "Rooms",
    			options,
    			id: create_fragment$2.name
    		});
    	}

    	get data() {
    		throw new Error_1$1("<Rooms>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set data(value) {
    		throw new Error_1$1("<Rooms>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/shared/AlertPopup.svelte generated by Svelte v3.59.1 */

    const file$1 = "src/shared/AlertPopup.svelte";

    function create_fragment$1(ctx) {
    	let div1;
    	let p;
    	let t0;
    	let t1;
    	let t2;
    	let div0;
    	let button0;
    	let t4;
    	let button1;

    	const block = {
    		c: function create() {
    			div1 = element("div");
    			p = element("p");
    			t0 = text("You got an invitation to a game from ");
    			t1 = text(/*invitationData*/ ctx[0]);
    			t2 = space();
    			div0 = element("div");
    			button0 = element("button");
    			button0.textContent = "Accept";
    			t4 = space();
    			button1 = element("button");
    			button1.textContent = "Decline";
    			attr_dev(p, "class", "svelte-1a07c20");
    			add_location(p, file$1, 5, 1, 69);
    			attr_dev(button0, "class", "accept-button svelte-1a07c20");
    			add_location(button0, file$1, 7, 3, 156);
    			attr_dev(button1, "class", "decline-button svelte-1a07c20");
    			add_location(button1, file$1, 8, 3, 205);
    			attr_dev(div0, "class", "buttons svelte-1a07c20");
    			add_location(div0, file$1, 6, 1, 131);
    			attr_dev(div1, "class", "popup svelte-1a07c20");
    			add_location(div1, file$1, 4, 0, 48);
    		},
    		l: function claim(nodes) {
    			throw new Error("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, div1, anchor);
    			append_dev(div1, p);
    			append_dev(p, t0);
    			append_dev(p, t1);
    			append_dev(div1, t2);
    			append_dev(div1, div0);
    			append_dev(div0, button0);
    			append_dev(div0, t4);
    			append_dev(div0, button1);
    		},
    		p: function update(ctx, [dirty]) {
    			if (dirty & /*invitationData*/ 1) set_data_dev(t1, /*invitationData*/ ctx[0]);
    		},
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(div1);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment$1.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance$1($$self, $$props, $$invalidate) {
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('AlertPopup', slots, []);
    	let { invitationData } = $$props;

    	$$self.$$.on_mount.push(function () {
    		if (invitationData === undefined && !('invitationData' in $$props || $$self.$$.bound[$$self.$$.props['invitationData']])) {
    			console.warn("<AlertPopup> was created without expected prop 'invitationData'");
    		}
    	});

    	const writable_props = ['invitationData'];

    	Object.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console.warn(`<AlertPopup> was created with unknown prop '${key}'`);
    	});

    	$$self.$$set = $$props => {
    		if ('invitationData' in $$props) $$invalidate(0, invitationData = $$props.invitationData);
    	};

    	$$self.$capture_state = () => ({ invitationData });

    	$$self.$inject_state = $$props => {
    		if ('invitationData' in $$props) $$invalidate(0, invitationData = $$props.invitationData);
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [invitationData];
    }

    class AlertPopup extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance$1, create_fragment$1, safe_not_equal, { invitationData: 0 });

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "AlertPopup",
    			options,
    			id: create_fragment$1.name
    		});
    	}

    	get invitationData() {
    		throw new Error("<AlertPopup>: Props cannot be read directly from the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}

    	set invitationData(value) {
    		throw new Error("<AlertPopup>: Props cannot be set directly on the component instance unless compiling with 'accessors: true' or '<svelte:options accessors/>'");
    	}
    }

    /* src/App.svelte generated by Svelte v3.59.1 */

    const { Error: Error_1, Object: Object_1, console: console_1 } = globals;
    const file = "src/App.svelte";

    // (149:0) {:catch error}
    function create_catch_block(ctx) {
    	let header;
    	let t0;
    	let h3;
    	let t1;
    	let t2_value = /*error*/ ctx[18].message + "";
    	let t2;
    	let current;

    	header = new Header({
    			props: {
    				img_path: /*img_path*/ ctx[0],
    				data: null
    			},
    			$$inline: true
    		});

    	const block = {
    		c: function create() {
    			create_component(header.$$.fragment);
    			t0 = space();
    			h3 = element("h3");
    			t1 = text("Error: ");
    			t2 = text(t2_value);
    			add_location(h3, file, 150, 1, 4209);
    		},
    		m: function mount(target, anchor) {
    			mount_component(header, target, anchor);
    			insert_dev(target, t0, anchor);
    			insert_dev(target, h3, anchor);
    			append_dev(h3, t1);
    			append_dev(h3, t2);
    			current = true;
    		},
    		p: function update(ctx, dirty) {
    			const header_changes = {};
    			if (dirty & /*img_path*/ 1) header_changes.img_path = /*img_path*/ ctx[0];
    			header.$set(header_changes);
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(header.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(header.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(header, detaching);
    			if (detaching) detach_dev(t0);
    			if (detaching) detach_dev(h3);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_catch_block.name,
    		type: "catch",
    		source: "(149:0) {:catch error}",
    		ctx
    	});

    	return block;
    }

    // (122:0) {:then dashboardData}
    function create_then_block(ctx) {
    	let header;
    	let t0;
    	let t1;
    	let show_if;
    	let current_block_type_index;
    	let if_block1;
    	let if_block1_anchor;
    	let current;

    	header = new Header({
    			props: {
    				img_path: /*img_path*/ ctx[0],
    				data: /*dashboardValue*/ ctx[2]
    			},
    			$$inline: true
    		});

    	let if_block0 = /*dashboardData*/ ctx[9] && /*isDFAActive*/ ctx[1] && create_if_block_7(ctx);
    	const if_block_creators = [create_if_block, create_if_block_6];
    	const if_blocks = [];

    	function select_block_type(ctx, dirty) {
    		if (dirty & /*isDFAActive*/ 2) show_if = null;
    		if (show_if == null) show_if = !!(/*dashboardData*/ ctx[9] && !/*isDFAActive*/ ctx[1] && Object.keys(/*dashboardData*/ ctx[9]).length > 0);
    		if (show_if) return 0;
    		if (!/*dashboardData*/ ctx[9]) return 1;
    		return -1;
    	}

    	if (~(current_block_type_index = select_block_type(ctx, -1))) {
    		if_block1 = if_blocks[current_block_type_index] = if_block_creators[current_block_type_index](ctx);
    	}

    	const block = {
    		c: function create() {
    			create_component(header.$$.fragment);
    			t0 = space();
    			if (if_block0) if_block0.c();
    			t1 = space();
    			if (if_block1) if_block1.c();
    			if_block1_anchor = empty$1();
    		},
    		m: function mount(target, anchor) {
    			mount_component(header, target, anchor);
    			insert_dev(target, t0, anchor);
    			if (if_block0) if_block0.m(target, anchor);
    			insert_dev(target, t1, anchor);

    			if (~current_block_type_index) {
    				if_blocks[current_block_type_index].m(target, anchor);
    			}

    			insert_dev(target, if_block1_anchor, anchor);
    			current = true;
    		},
    		p: function update(ctx, dirty) {
    			const header_changes = {};
    			if (dirty & /*img_path*/ 1) header_changes.img_path = /*img_path*/ ctx[0];
    			if (dirty & /*dashboardValue*/ 4) header_changes.data = /*dashboardValue*/ ctx[2];
    			header.$set(header_changes);

    			if (/*dashboardData*/ ctx[9] && /*isDFAActive*/ ctx[1]) {
    				if (if_block0) {
    					if_block0.p(ctx, dirty);

    					if (dirty & /*isDFAActive*/ 2) {
    						transition_in(if_block0, 1);
    					}
    				} else {
    					if_block0 = create_if_block_7(ctx);
    					if_block0.c();
    					transition_in(if_block0, 1);
    					if_block0.m(t1.parentNode, t1);
    				}
    			} else if (if_block0) {
    				group_outros();

    				transition_out(if_block0, 1, 1, () => {
    					if_block0 = null;
    				});

    				check_outros();
    			}

    			let previous_block_index = current_block_type_index;
    			current_block_type_index = select_block_type(ctx, dirty);

    			if (current_block_type_index === previous_block_index) {
    				if (~current_block_type_index) {
    					if_blocks[current_block_type_index].p(ctx, dirty);
    				}
    			} else {
    				if (if_block1) {
    					group_outros();

    					transition_out(if_blocks[previous_block_index], 1, 1, () => {
    						if_blocks[previous_block_index] = null;
    					});

    					check_outros();
    				}

    				if (~current_block_type_index) {
    					if_block1 = if_blocks[current_block_type_index];

    					if (!if_block1) {
    						if_block1 = if_blocks[current_block_type_index] = if_block_creators[current_block_type_index](ctx);
    						if_block1.c();
    					} else {
    						if_block1.p(ctx, dirty);
    					}

    					transition_in(if_block1, 1);
    					if_block1.m(if_block1_anchor.parentNode, if_block1_anchor);
    				} else {
    					if_block1 = null;
    				}
    			}
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(header.$$.fragment, local);
    			transition_in(if_block0);
    			transition_in(if_block1);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(header.$$.fragment, local);
    			transition_out(if_block0);
    			transition_out(if_block1);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(header, detaching);
    			if (detaching) detach_dev(t0);
    			if (if_block0) if_block0.d(detaching);
    			if (detaching) detach_dev(t1);

    			if (~current_block_type_index) {
    				if_blocks[current_block_type_index].d(detaching);
    			}

    			if (detaching) detach_dev(if_block1_anchor);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_then_block.name,
    		type: "then",
    		source: "(122:0) {:then dashboardData}",
    		ctx
    	});

    	return block;
    }

    // (124:1) {#if dashboardData && isDFAActive}
    function create_if_block_7(ctx) {
    	let dfahomepage;
    	let updating_isDFAActive;
    	let current;

    	function dfahomepage_isDFAActive_binding(value) {
    		/*dfahomepage_isDFAActive_binding*/ ctx[10](value);
    	}

    	let dfahomepage_props = { data: /*dashboardValue*/ ctx[2] };

    	if (/*isDFAActive*/ ctx[1] !== void 0) {
    		dfahomepage_props.isDFAActive = /*isDFAActive*/ ctx[1];
    	}

    	dfahomepage = new DfaHomePage({ props: dfahomepage_props, $$inline: true });
    	binding_callbacks.push(() => bind$1(dfahomepage, 'isDFAActive', dfahomepage_isDFAActive_binding));
    	dfahomepage.$on("updateVerification", /*verified*/ ctx[8]);

    	const block = {
    		c: function create() {
    			create_component(dfahomepage.$$.fragment);
    		},
    		m: function mount(target, anchor) {
    			mount_component(dfahomepage, target, anchor);
    			current = true;
    		},
    		p: function update(ctx, dirty) {
    			const dfahomepage_changes = {};
    			if (dirty & /*dashboardValue*/ 4) dfahomepage_changes.data = /*dashboardValue*/ ctx[2];

    			if (!updating_isDFAActive && dirty & /*isDFAActive*/ 2) {
    				updating_isDFAActive = true;
    				dfahomepage_changes.isDFAActive = /*isDFAActive*/ ctx[1];
    				add_flush_callback(() => updating_isDFAActive = false);
    			}

    			dfahomepage.$set(dfahomepage_changes);
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(dfahomepage.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(dfahomepage.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(dfahomepage, detaching);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_7.name,
    		type: "if",
    		source: "(124:1) {#if dashboardData && isDFAActive}",
    		ctx
    	});

    	return block;
    }

    // (145:27) 
    function create_if_block_6(ctx) {
    	let login;
    	let current;
    	login = new Login({ $$inline: true });

    	const block = {
    		c: function create() {
    			create_component(login.$$.fragment);
    		},
    		m: function mount(target, anchor) {
    			mount_component(login, target, anchor);
    			current = true;
    		},
    		p: noop$1,
    		i: function intro(local) {
    			if (current) return;
    			transition_in(login.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(login.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(login, detaching);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_6.name,
    		type: "if",
    		source: "(145:27) ",
    		ctx
    	});

    	return block;
    }

    // (127:1) {#if dashboardData && !isDFAActive && Object.keys(dashboardData).length > 0}
    function create_if_block(ctx) {
    	let tabs;
    	let t0;
    	let main;
    	let div;
    	let current_block_type_index;
    	let if_block0;
    	let t1;
    	let current;

    	tabs = new Tabs({
    			props: { id: /*dashboardData*/ ctx[9].id },
    			$$inline: true
    		});

    	const if_block_creators = [create_if_block_2, create_if_block_3, create_if_block_4, create_if_block_5];
    	const if_blocks = [];

    	function select_block_type_1(ctx, dirty) {
    		if (/*$page_shown*/ ctx[5] == "/") return 0;
    		if (/*$page_shown*/ ctx[5] == "game") return 1;
    		if (/*$page_shown*/ ctx[5] == "chat") return 2;
    		if (/*$page_shown*/ ctx[5] === "room") return 3;
    		return -1;
    	}

    	if (~(current_block_type_index = select_block_type_1(ctx))) {
    		if_block0 = if_blocks[current_block_type_index] = if_block_creators[current_block_type_index](ctx);
    	}

    	let if_block1 = /*alertPopupOn*/ ctx[3] && create_if_block_1(ctx);

    	const block = {
    		c: function create() {
    			create_component(tabs.$$.fragment);
    			t0 = space();
    			main = element("main");
    			div = element("div");
    			if (if_block0) if_block0.c();
    			t1 = space();
    			if (if_block1) if_block1.c();
    			attr_dev(div, "class", "main_body svelte-1ipp7uf");
    			add_location(div, file, 129, 3, 3620);
    			attr_dev(main, "class", "svelte-1ipp7uf");
    			add_location(main, file, 128, 2, 3610);
    		},
    		m: function mount(target, anchor) {
    			mount_component(tabs, target, anchor);
    			insert_dev(target, t0, anchor);
    			insert_dev(target, main, anchor);
    			append_dev(main, div);

    			if (~current_block_type_index) {
    				if_blocks[current_block_type_index].m(div, null);
    			}

    			append_dev(main, t1);
    			if (if_block1) if_block1.m(main, null);
    			current = true;
    		},
    		p: function update(ctx, dirty) {
    			let previous_block_index = current_block_type_index;
    			current_block_type_index = select_block_type_1(ctx);

    			if (current_block_type_index === previous_block_index) {
    				if (~current_block_type_index) {
    					if_blocks[current_block_type_index].p(ctx, dirty);
    				}
    			} else {
    				if (if_block0) {
    					group_outros();

    					transition_out(if_blocks[previous_block_index], 1, 1, () => {
    						if_blocks[previous_block_index] = null;
    					});

    					check_outros();
    				}

    				if (~current_block_type_index) {
    					if_block0 = if_blocks[current_block_type_index];

    					if (!if_block0) {
    						if_block0 = if_blocks[current_block_type_index] = if_block_creators[current_block_type_index](ctx);
    						if_block0.c();
    					} else {
    						if_block0.p(ctx, dirty);
    					}

    					transition_in(if_block0, 1);
    					if_block0.m(div, null);
    				} else {
    					if_block0 = null;
    				}
    			}

    			if (/*alertPopupOn*/ ctx[3]) {
    				if (if_block1) {
    					if_block1.p(ctx, dirty);

    					if (dirty & /*alertPopupOn*/ 8) {
    						transition_in(if_block1, 1);
    					}
    				} else {
    					if_block1 = create_if_block_1(ctx);
    					if_block1.c();
    					transition_in(if_block1, 1);
    					if_block1.m(main, null);
    				}
    			} else if (if_block1) {
    				group_outros();

    				transition_out(if_block1, 1, 1, () => {
    					if_block1 = null;
    				});

    				check_outros();
    			}
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(tabs.$$.fragment, local);
    			transition_in(if_block0);
    			transition_in(if_block1);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(tabs.$$.fragment, local);
    			transition_out(if_block0);
    			transition_out(if_block1);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(tabs, detaching);
    			if (detaching) detach_dev(t0);
    			if (detaching) detach_dev(main);

    			if (~current_block_type_index) {
    				if_blocks[current_block_type_index].d();
    			}

    			if (if_block1) if_block1.d();
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block.name,
    		type: "if",
    		source: "(127:1) {#if dashboardData && !isDFAActive && Object.keys(dashboardData).length > 0}",
    		ctx
    	});

    	return block;
    }

    // (137:37) 
    function create_if_block_5(ctx) {
    	let rooms_1;
    	let current;

    	rooms_1 = new Rooms({
    			props: { data: /*dashboardValue*/ ctx[2] },
    			$$inline: true
    		});

    	const block = {
    		c: function create() {
    			create_component(rooms_1.$$.fragment);
    		},
    		m: function mount(target, anchor) {
    			mount_component(rooms_1, target, anchor);
    			current = true;
    		},
    		p: function update(ctx, dirty) {
    			const rooms_1_changes = {};
    			if (dirty & /*dashboardValue*/ 4) rooms_1_changes.data = /*dashboardValue*/ ctx[2];
    			rooms_1.$set(rooms_1_changes);
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(rooms_1.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(rooms_1.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(rooms_1, detaching);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_5.name,
    		type: "if",
    		source: "(137:37) ",
    		ctx
    	});

    	return block;
    }

    // (135:36) 
    function create_if_block_4(ctx) {
    	let chat;
    	let current;

    	chat = new Chat({
    			props: {
    				data: /*dashboardValue*/ ctx[2],
    				socket: getSocket()
    			},
    			$$inline: true
    		});

    	const block = {
    		c: function create() {
    			create_component(chat.$$.fragment);
    		},
    		m: function mount(target, anchor) {
    			mount_component(chat, target, anchor);
    			current = true;
    		},
    		p: function update(ctx, dirty) {
    			const chat_changes = {};
    			if (dirty & /*dashboardValue*/ 4) chat_changes.data = /*dashboardValue*/ ctx[2];
    			chat.$set(chat_changes);
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(chat.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(chat.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(chat, detaching);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_4.name,
    		type: "if",
    		source: "(135:36) ",
    		ctx
    	});

    	return block;
    }

    // (133:36) 
    function create_if_block_3(ctx) {
    	let game;
    	let current;

    	game = new Pong({
    			props: { socket: getSocket() },
    			$$inline: true
    		});

    	const block = {
    		c: function create() {
    			create_component(game.$$.fragment);
    		},
    		m: function mount(target, anchor) {
    			mount_component(game, target, anchor);
    			current = true;
    		},
    		p: noop$1,
    		i: function intro(local) {
    			if (current) return;
    			transition_in(game.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(game.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(game, detaching);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_3.name,
    		type: "if",
    		source: "(133:36) ",
    		ctx
    	});

    	return block;
    }

    // (131:4) {#if $page_shown == "/"}
    function create_if_block_2(ctx) {
    	let dashboard;
    	let current;

    	dashboard = new Dashboard({
    			props: {
    				data: /*dashboardValue*/ ctx[2],
    				targetId: /*dashboardData*/ ctx[9].id
    			},
    			$$inline: true
    		});

    	dashboard.$on("updateProfile", /*newProfileData*/ ctx[7]);

    	const block = {
    		c: function create() {
    			create_component(dashboard.$$.fragment);
    		},
    		m: function mount(target, anchor) {
    			mount_component(dashboard, target, anchor);
    			current = true;
    		},
    		p: function update(ctx, dirty) {
    			const dashboard_changes = {};
    			if (dirty & /*dashboardValue*/ 4) dashboard_changes.data = /*dashboardValue*/ ctx[2];
    			dashboard.$set(dashboard_changes);
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(dashboard.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(dashboard.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(dashboard, detaching);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_2.name,
    		type: "if",
    		source: "(131:4) {#if $page_shown == \\\"/\\\"}",
    		ctx
    	});

    	return block;
    }

    // (141:3) {#if alertPopupOn}
    function create_if_block_1(ctx) {
    	let alertpopup;
    	let current;

    	alertpopup = new AlertPopup({
    			props: {
    				invitationData: /*invitationData*/ ctx[4]
    			},
    			$$inline: true
    		});

    	const block = {
    		c: function create() {
    			create_component(alertpopup.$$.fragment);
    		},
    		m: function mount(target, anchor) {
    			mount_component(alertpopup, target, anchor);
    			current = true;
    		},
    		p: function update(ctx, dirty) {
    			const alertpopup_changes = {};
    			if (dirty & /*invitationData*/ 16) alertpopup_changes.invitationData = /*invitationData*/ ctx[4];
    			alertpopup.$set(alertpopup_changes);
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(alertpopup.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			transition_out(alertpopup.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			destroy_component(alertpopup, detaching);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_if_block_1.name,
    		type: "if",
    		source: "(141:3) {#if alertPopupOn}",
    		ctx
    	});

    	return block;
    }

    // (119:20)  <center><p>Loading...</p></center>  {:then dashboardData}
    function create_pending_block(ctx) {
    	let center;
    	let p;

    	const block = {
    		c: function create() {
    			center = element("center");
    			p = element("p");
    			p.textContent = "Loading...";
    			add_location(p, file, 119, 8, 3255);
    			add_location(center, file, 119, 0, 3247);
    		},
    		m: function mount(target, anchor) {
    			insert_dev(target, center, anchor);
    			append_dev(center, p);
    		},
    		p: noop$1,
    		i: noop$1,
    		o: noop$1,
    		d: function destroy(detaching) {
    			if (detaching) detach_dev(center);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_pending_block.name,
    		type: "pending",
    		source: "(119:20)  <center><p>Loading...</p></center>  {:then dashboardData}",
    		ctx
    	});

    	return block;
    }

    function create_fragment(ctx) {
    	let t;
    	let footer;
    	let current;

    	let info = {
    		ctx,
    		current: null,
    		token: null,
    		hasCatch: true,
    		pending: create_pending_block,
    		then: create_then_block,
    		catch: create_catch_block,
    		value: 9,
    		error: 18,
    		blocks: [,,,]
    	};

    	handle_promise(/*fetchData*/ ctx[6](), info);
    	footer = new Footer({ $$inline: true });

    	const block = {
    		c: function create() {
    			info.block.c();
    			t = space();
    			create_component(footer.$$.fragment);
    		},
    		l: function claim(nodes) {
    			throw new Error_1("options.hydrate only works if the component was compiled with the `hydratable: true` option");
    		},
    		m: function mount(target, anchor) {
    			info.block.m(target, info.anchor = anchor);
    			info.mount = () => t.parentNode;
    			info.anchor = t;
    			insert_dev(target, t, anchor);
    			mount_component(footer, target, anchor);
    			current = true;
    		},
    		p: function update(new_ctx, [dirty]) {
    			ctx = new_ctx;
    			update_await_block_branch(info, ctx, dirty);
    		},
    		i: function intro(local) {
    			if (current) return;
    			transition_in(info.block);
    			transition_in(footer.$$.fragment, local);
    			current = true;
    		},
    		o: function outro(local) {
    			for (let i = 0; i < 3; i += 1) {
    				const block = info.blocks[i];
    				transition_out(block);
    			}

    			transition_out(footer.$$.fragment, local);
    			current = false;
    		},
    		d: function destroy(detaching) {
    			info.block.d(detaching);
    			info.token = null;
    			info = null;
    			if (detaching) detach_dev(t);
    			destroy_component(footer, detaching);
    		}
    	};

    	dispatch_dev("SvelteRegisterBlock", {
    		block,
    		id: create_fragment.name,
    		type: "component",
    		source: "",
    		ctx
    	});

    	return block;
    }

    function instance($$self, $$props, $$invalidate) {
    	let $userId42;
    	let $page_shown;
    	validate_store(userId42, 'userId42');
    	component_subscribe($$self, userId42, $$value => $$invalidate(12, $userId42 = $$value));
    	validate_store(page_shown, 'page_shown');
    	component_subscribe($$self, page_shown, $$value => $$invalidate(5, $page_shown = $$value));
    	let { $$slots: slots = {}, $$scope } = $$props;
    	validate_slots('App', slots, []);
    	history.replaceState({ "href_to_show": "/" }, "", "/");

    	window.addEventListener("popstate", e => {
    		console.log(e.state.href_to_show);
    		set_store_value(page_shown, $page_shown = e.state.href_to_show, $page_shown);
    	});

    	let img_path;
    	let id;
    	let isDFAActive;
    	let dashboardValue = null;
    	let alertPopupOn = false;
    	let invitationData = null;
    	let alertNumber = 0; //nombres de messages reçu non lu
    	let dashboardData = fetchData();

    	// ce qui est en dessous est une abomination
    	// c'est sans doute le Frankestein de notre generation
    	let done = initializeSocket(dashboardData);

    	async function setPopupToogleEvent() {
    		await done;
    		getSocket().chat.on('invitationGame', invitationHandler);
    	}

    	setPopupToogleEvent();

    	let invitationHandler = opponent_id => {
    		$$invalidate(3, alertPopupOn = true);
    		$$invalidate(4, invitationData = opponent_id);
    	}; //alert("Some guy invited you to a game!");

    	// Le Frankenstein sarrete ici
    	async function fetchData() {
    		if (!document.cookie) return;

    		try {
    			console.log(document.cookie);
    			const cookieValue = document.cookie.split('; ').find(cookie => cookie.startsWith('jwt_cookie')).split('=')[1];
    			const id42 = document.cookie.split('; ').find(cookie => cookie.startsWith('id42')).split('=')[1];
    			set_store_value(userId42, $userId42 = id42, $userId42);

    			const response = await fetch(`http://${hostname}:3000/dashboard/${id42}`, {
    				headers: { 'Authorization': `Bearer ${cookieValue}` }
    			});

    			if (response.ok) {
    				const data = await response.json();
    				if (data.img !== "undefined") $$invalidate(0, img_path = data.img); else $$invalidate(0, img_path = "img/il_794xN.3892173164_egqv.avif");
    				$$invalidate(2, dashboardValue = data);
    				id = data.id;
    				$$invalidate(1, isDFAActive = data.Dfa);
    				return data;
    			} else {
    				throw new Error('Failed to fetch dashboard data');
    			}
    		} catch(error) {
    			console.error(error);
    		}
    	}

    	const newProfileData = event => {
    		console.log(event.detail);
    		$$invalidate(2, dashboardValue = event.detail);
    		$$invalidate(0, img_path = dashboardValue.img);
    	};

    	async function verified() {
    		await toggleDFAState();
    		$$invalidate(2, dashboardValue = await fetchData());
    		$$invalidate(1, isDFAActive = false);
    	}

    	async function toggleDFAState() {
    		$$invalidate(1, isDFAActive = true);

    		try {
    			const response = await axios$1.post(`http://${hostname}:3000/auth/2fa/${id}`, { isDFAActive });
    			console.log('DFA status updated in the database to true');
    		} catch(error) {
    			console.error('Failed to update DFA status: ', error);
    		}
    	}

    	const writable_props = [];

    	Object_1.keys($$props).forEach(key => {
    		if (!~writable_props.indexOf(key) && key.slice(0, 2) !== '$$' && key !== 'slot') console_1.warn(`<App> was created with unknown prop '${key}'`);
    	});

    	function dfahomepage_isDFAActive_binding(value) {
    		isDFAActive = value;
    		$$invalidate(1, isDFAActive);
    	}

    	$$self.$capture_state = () => ({
    		Login,
    		DfaHomePage,
    		Header,
    		Footer,
    		Tabs,
    		Dashboard,
    		Chat,
    		Game: Pong,
    		Rooms,
    		userId42,
    		page_shown,
    		hostname,
    		axios: axios$1,
    		getSocket,
    		initializeSocket,
    		rooms: rooms$1,
    		onMount,
    		AlertPopup,
    		Invitation,
    		img_path,
    		id,
    		isDFAActive,
    		dashboardValue,
    		alertPopupOn,
    		invitationData,
    		alertNumber,
    		dashboardData,
    		done,
    		setPopupToogleEvent,
    		invitationHandler,
    		fetchData,
    		newProfileData,
    		verified,
    		toggleDFAState,
    		$userId42,
    		$page_shown
    	});

    	$$self.$inject_state = $$props => {
    		if ('img_path' in $$props) $$invalidate(0, img_path = $$props.img_path);
    		if ('id' in $$props) id = $$props.id;
    		if ('isDFAActive' in $$props) $$invalidate(1, isDFAActive = $$props.isDFAActive);
    		if ('dashboardValue' in $$props) $$invalidate(2, dashboardValue = $$props.dashboardValue);
    		if ('alertPopupOn' in $$props) $$invalidate(3, alertPopupOn = $$props.alertPopupOn);
    		if ('invitationData' in $$props) $$invalidate(4, invitationData = $$props.invitationData);
    		if ('alertNumber' in $$props) alertNumber = $$props.alertNumber;
    		if ('dashboardData' in $$props) $$invalidate(9, dashboardData = $$props.dashboardData);
    		if ('done' in $$props) done = $$props.done;
    		if ('invitationHandler' in $$props) invitationHandler = $$props.invitationHandler;
    	};

    	if ($$props && "$$inject" in $$props) {
    		$$self.$inject_state($$props.$$inject);
    	}

    	return [
    		img_path,
    		isDFAActive,
    		dashboardValue,
    		alertPopupOn,
    		invitationData,
    		$page_shown,
    		fetchData,
    		newProfileData,
    		verified,
    		dashboardData,
    		dfahomepage_isDFAActive_binding
    	];
    }

    class App extends SvelteComponentDev {
    	constructor(options) {
    		super(options);
    		init(this, options, instance, create_fragment, safe_not_equal, {});

    		dispatch_dev("SvelteRegisterComponent", {
    			component: this,
    			tagName: "App",
    			options,
    			id: create_fragment.name
    		});
    	}
    }

    // import apiClient from './api';
    // import dotenv from 'dotenv';
    // dotenv.config();

    const app = new App({
    	target: document.body,
    	/*	props: {
    		name: 'world'
    	}*/
    });

    return app;

})(environment, colyseus_js);
//# sourceMappingURL=bundle.js.map
