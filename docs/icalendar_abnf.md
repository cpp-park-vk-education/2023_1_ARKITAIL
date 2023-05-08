Грамматика спецификации [iCalendar (RFC 5545)](https://icalendar.org/RFC-Specifications/iCalendar-RFC-5545/) 
в форме [ABNF (RFC 5234)](https://datatracker.ietf.org/doc/html/rfc5234). Для
удобства всё собрано в одном файле.

[3.1. Content Lines](https://icalendar.org/iCalendar-RFC-5545/3-1-content-lines.html)

```
contentline   = name *(";" param ) ":" value CRLF
; This ABNF is just a general definition for an initial parsing
; of the content line into its property name, parameter list,
; and value string

; When parsing a content line, folded lines MUST first
; be unfolded according to the unfolding procedure
; described above.  When generating a content line, lines
; longer than 75 octets SHOULD be folded according to
; the folding procedure described above.

name          = iana-oken / x-name

iana-token    = 1*(ALPHA / DIGIT / "-")
; iCalendar identifier registered with IANA

x-name        = "X-" [vendorid "-"] 1*(ALPHA / DIGIT / "-")
; Reserved for experimental use.

vendorid      = 3*(ALPHA / DIGIT)
; Vendor identification

param         = param-name "=" param-value *("," param-value)
; Each property defines the specific ABNF for the parameters
; allowed on the property.  Refer to specific properties for
; precise parameter ABNF.

param-name    = iana-token / x-name

param-value   = paramtext / quoted-string

paramtext     = *SAFE-CHAR

value         = *VALUE-CHAR

quoted-string = DQUOTE *QSAFE-CHAR DQUOTE

QSAFE-CHAR    = WSP / %x21 / %x23-7E / NON-US-ASCII
; Any character except CONTROL and DQUOTE

SAFE-CHAR     = WSP / %x21 / %x23-2B / %x2D-39 / %x3C-7E
           / NON-US-ASCII
; Any character except CONTROL, DQUOTE, ";", ":", ","

VALUE-CHAR    = WSP / %x21-7E / NON-US-ASCII
; Any textual character

NON-US-ASCII  = UTF8-2 / UTF8-3 / UTF8-4
; UTF8-2, UTF8-3, and UTF8-4 are defined in [RFC3629]

CONTROL       = %x00-08 / %x0A-1F / %x7F
; All the controls except HTAB
```

[3.2. Property Parameters](https://icalendar.org/iCalendar-RFC-5545/3-2-property-parameters.html)

```
other-param   = (iana-param / x-param)

iana-param  = iana-token "=" param-value *("," param-value)
; Some other IANA-registered iCalendar parameter.

x-param     = x-name "=" param-value *("," param-value)
; A non-standard, experimental parameter.
```

[3.2.1. Alternate Text Representation](https://icalendar.org/iCalendar-RFC-5545/3-2-1-alternate-text-representation.html)

```
altrepparam = "ALTREP" "=" DQUOTE uri DQUOTE
```

[3.2.2. Common Name](https://icalendar.org/iCalendar-RFC-5545/3-2-2-common-name.html)

```
cnparam    = "CN" "=" param-value
```

[3.2.3. Calendar User Type](https://icalendar.org/iCalendar-RFC-5545/3-2-3-calendar-user-type.html)

```
cutypeparam        = "CUTYPE" "="
                   ("INDIVIDUAL"   ; An individual
                  / "GROUP"        ; A group of individuals
                  / "RESOURCE"     ; A physical resource
                  / "ROOM"         ; A room resource
                  / "UNKNOWN"      ; Otherwise not known
                  / x-name         ; Experimental type
                  / iana-token)    ; Other IANA-registered
                                   ; type
; Default is INDIVIDUAL
```

[3.2.4. Delegators](https://icalendar.org/iCalendar-RFC-5545/3-2-4-delegators.html)

```
delfromparam       = "DELEGATED-FROM" "=" DQUOTE cal-address
                      DQUOTE *("," DQUOTE cal-address DQUOTE)
```

[3.2.5. Delegatees](https://icalendar.org/iCalendar-RFC-5545/3-2-5-delegatees.html)

```
deltoparam = "DELEGATED-TO" "=" DQUOTE cal-address DQUOTE
             *("," DQUOTE cal-address DQUOTE)
```

[3.2.6. Directory Entry Reference](https://icalendar.org/iCalendar-RFC-5545/3-2-6-directory-entry-reference.html)

```
dirparam   = "DIR" "=" DQUOTE uri DQUOTE
```

[3.2.7. Inline Encoding](https://icalendar.org/iCalendar-RFC-5545/3-2-7-inline-encoding.html)

```
encodingparam      = "ENCODING" "="
                   ( "8BIT"
   ; "8bit" text encoding is defined in [RFC2045]
                   / "BASE64"
   ; "BASE64" binary encoding format is defined in [RFC4648]
                   )
```

[3.2.8. Format Type](https://icalendar.org/iCalendar-RFC-5545/3-2-8-format-type.html)

```
fmttypeparam = "FMTTYPE" "=" type-name "/" subtype-name
               ; Where "type-name" and "subtype-name" are
               ; defined in Section 4.2 of [RFC4288].
```

[3.2.9. Free/Busy Time Type](https://icalendar.org/iCalendar-RFC-5545/3-2-9-free-busy-time-type.html)

```
fbtypeparam        = "FBTYPE" "=" ("FREE" / "BUSY"
                   / "BUSY-UNAVAILABLE" / "BUSY-TENTATIVE"
                   / x-name
         ; Some experimental iCalendar free/busy type.
                   / iana-token)
         ; Some other IANA-registered iCalendar free/busy type.
```

[3.2.10. Language](https://icalendar.org/iCalendar-RFC-5545/3-2-10-language.html)

```
languageparam = "LANGUAGE" "=" language

language = Language-Tag
           ; As defined in [RFC5646].
```

[3.2.11. Group or List Membership](https://icalendar.org/iCalendar-RFC-5545/3-2-11-group-or-list-membership.html)

```
memberparam        = "MEMBER" "=" DQUOTE cal-address DQUOTE
                     *("," DQUOTE cal-address DQUOTE)
```

[3.2.12. Participation Status](https://icalendar.org/iCalendar-RFC-5545/3-2-12-participation-status.html)

```
partstatparam    = "PARTSTAT" "="
                  (partstat-event
                 / partstat-todo
                 / partstat-jour)

partstat-event   = ("NEEDS-ACTION"    ; Event needs action
                 / "ACCEPTED"         ; Event accepted
                 / "DECLINED"         ; Event declined
                 / "TENTATIVE"        ; Event tentatively
                                      ; accepted
                 / "DELEGATED"        ; Event delegated
                 / x-name             ; Experimental status
                 / iana-token)        ; Other IANA-registered
                                      ; status
; These are the participation statuses for a "VEVENT".
; Default is NEEDS-ACTION.

partstat-todo    = ("NEEDS-ACTION"    ; To-do needs action
                 / "ACCEPTED"         ; To-do accepted
                 / "DECLINED"         ; To-do declined
                 / "TENTATIVE"        ; To-do tentatively
                                      ; accepted
                 / "DELEGATED"        ; To-do delegated
                 / "COMPLETED"        ; To-do completed
                                      ; COMPLETED property has
                                      ; DATE-TIME completed
                 / "IN-PROCESS"       ; To-do in process of
                                      ; being completed
                 / x-name             ; Experimental status
                 / iana-token)        ; Other IANA-registered
                                      ; status
; These are the participation statuses for a "VTODO".
; Default is NEEDS-ACTION.

partstat-jour    = ("NEEDS-ACTION"    ; Journal needs action
                 / "ACCEPTED"         ; Journal accepted
                 / "DECLINED"         ; Journal declined
                 / x-name             ; Experimental status
                 / iana-token)        ; Other IANA-registered
                                      ; status
; These are the participation statuses for a "VJOURNAL".
; Default is NEEDS-ACTION.
```

[3.2.13. Recurrence Identifier Range](https://icalendar.org/iCalendar-RFC-5545/3-2-13-recurrence-identifier-range.html)

```
rangeparam = "RANGE" "=" "THISANDFUTURE"
```

[3.2.14. Alarm Trigger Relationship](https://icalendar.org/iCalendar-RFC-5545/3-2-14-alarm-trigger-relationship.html)

```
trigrelparam       = "RELATED" "="
                    ("START"       ; Trigger off of start
                   / "END")        ; Trigger off of end
```

[3.2.15. Relationship Type](https://icalendar.org/iCalendar-RFC-5545/3-2-15-relationship-type.html)

```
reltypeparam       = "RELTYPE" "="
                    ("PARENT"    ; Parent relationship - Default
                   / "CHILD"     ; Child relationship
                   / "SIBLING"   ; Sibling relationship
                   / iana-token  ; Some other IANA-registered
                                 ; iCalendar relationship type
                   / x-name)     ; A non-standard, experimental
                                 ; relationship type
```

[3.2.16. Participation Role](https://icalendar.org/iCalendar-RFC-5545/3-2-16-participation-role.html)

```
roleparam = "ROLE" "=" ("CHAIR"
          ; Indicates chair of the
          ; calendar entity 
          / "REQ-PARTICIPANT" ; Indicates a participant whose 
          ; participation is required 
          / "OPT-PARTICIPANT" 
          ; Indicates a participant whose
          ; participation is optional
          / "NON-PARTICIPANT"
          ; Indicates a participant who
          ; is copied for information
          ; purposes only
          / x-name
          ; Experimental role
          / iana-token)
          ; Other IANA role
          ; Default is REQ-PARTICIPANT
```

[3.2.17. RSVP Expectation](https://icalendar.org/iCalendar-RFC-5545/3-2-17-rsvp-expectation.html)

```
rsvpparam = "RSVP" "=" ("TRUE" / "FALSE")
; Default is FALSE
```

[3.2.18. Sent By](https://icalendar.org/iCalendar-RFC-5545/3-2-18-sent-by.html)

```
sentbyparam        = "SENT-BY" "=" DQUOTE cal-address DQUOTE
```

[3.2.19. Time Zone Identifier](https://icalendar.org/iCalendar-RFC-5545/3-2-19-time-zone-identifier.html)

```
tzidparam  = "TZID" "=" [tzidprefix] paramtext

tzidprefix = "/"
```

[3.2.20. Value Data Types](https://icalendar.org/iCalendar-RFC-5545/3-2-20-value-data-types.html)

```
valuetypeparam = "VALUE" "=" valuetype

valuetype  = ("BINARY"
           / "BOOLEAN"
           / "CAL-ADDRESS"
           / "DATE"
           / "DATE-TIME"
           / "DURATION"
           / "FLOAT"
           / "INTEGER"
           / "PERIOD"
           / "RECUR"
           / "TEXT"
           / "TIME"
           / "URI"
           / "UTC-OFFSET"
           / x-name
           ; Some experimental iCalendar value type.
           / iana-token)
           ; Some other IANA-registered iCalendar value type.
```

[3.3.1. Binary](https://icalendar.org/iCalendar-RFC-5545/3-3-1-binary.html)

```
binary     = *(4b-char) [b-end]
; A "BASE64" encoded character string, as defined by [RFC4648].

b-end      = (2b-char "==") / (3b-char "=")

b-char = ALPHA / DIGIT / "+" / "/"
```

[3.3.2. Boolean](https://icalendar.org/iCalendar-RFC-5545/3-3-2-boolean.html)

```
boolean    = "TRUE" / "FALSE"
```

[3.3.3. Calendar User Address](https://icalendar.org/iCalendar-RFC-5545/3-3-3-calendar-user-address.html)

```
cal-address        = uri
```

[3.3.4. Date](https://icalendar.org/iCalendar-RFC-5545/3-3-4-date.html)

```
date               = date-value

date-value         = date-fullyear date-month date-mday
date-fullyear      = 4DIGIT
date-month         = 2DIGIT        ;01-12
date-mday          = 2DIGIT        ;01-28, 01-29, 01-30, 01-31
                                   ;based on month/year
```

[3.3.5. Date-Time](https://icalendar.org/iCalendar-RFC-5545/3-3-5-date-time.html)

```
date-time  = date "T" time ;As specified in the DATE and TIME
                           ;value definitions
```

[3.3.6. Duration](https://icalendar.org/iCalendar-RFC-5545/3-3-6-duration.html)

```
dur-value  = (["+"] / "-") "P" (dur-date / dur-time / dur-week)

dur-date   = dur-day [dur-time]
dur-time   = "T" (dur-hour / dur-minute / dur-second)
dur-week   = 1*DIGIT "W"
dur-hour   = 1*DIGIT "H" [dur-minute]
dur-minute = 1*DIGIT "M" [dur-second]
dur-second = 1*DIGIT "S"
dur-day    = 1*DIGIT "D"
```

[3.3.7. Float](https://icalendar.org/iCalendar-RFC-5545/3-3-7-float.html)

```
float      = (["+"] / "-") 1*DIGIT ["." 1*DIGIT]
```

[3.3.8. Integer](https://icalendar.org/iCalendar-RFC-5545/3-3-8-integer.html)

```
integer    = (["+"] / "-") 1*DIGIT
```

[3.3.9. Period of Time](https://icalendar.org/iCalendar-RFC-5545/3-3-9-period-of-time.html)

```
period     = period-explicit / period-start

period-explicit = date-time "/" date-time
; [ISO.8601.2004] complete representation basic format for a
; period of time consisting of a start and end.  The start MUST
; be before the end.

period-start = date-time "/" dur-value
; [ISO.8601.2004] complete representation basic format for a
; period of time consisting of a start and positive duration
; of time.

Description:  If the property permits, multiple "period" values are
specified by a COMMA-separated list of values.  There are two
forms of a period of time.  First, a period of time is identified
by its start and its end.  This format is based on the
[ISO.8601.2004] complete representation, basic format for "DATE-
TIME" start of the period, followed by a SOLIDUS character
followed by the "DATE-TIME" of the end of the period.  The start
of the period MUST be before the end of the period.  Second, a
period of time can also be defined by a start and a positive
duration of time.  The format is based on the [ISO.8601.2004]
complete representation, basic format for the "DATE-TIME" start of
the period, followed by a SOLIDUS character, followed by the
[ISO.8601.2004] basic format for "DURATION" of the period.
```

[3.3.10. Recurrence Rule](https://icalendar.org/iCalendar-RFC-5545/3-3-10-recurrence-rule.html)

```
recur           = recur-rule-part *( ";" recur-rule-part )
                ;
                ; The rule parts are not ordered in any
                ; particular sequence.
                ;
                ; The FREQ rule part is REQUIRED,
                ; but MUST NOT occur more than once.
                ;
                ; The UNTIL or COUNT rule parts are OPTIONAL,
                ; but they MUST NOT occur in the same 'recur'.
                ;
                ; The other rule parts are OPTIONAL,
                ; but MUST NOT occur more than once.

recur-rule-part = ( "FREQ" "=" freq )
                / ( "UNTIL" "=" enddate )
                / ( "COUNT" "=" 1*DIGIT )
                / ( "INTERVAL" "=" 1*DIGIT )
                / ( "BYSECOND" "=" byseclist )
                / ( "BYMINUTE" "=" byminlist )
                / ( "BYHOUR" "=" byhrlist )
                / ( "BYDAY" "=" bywdaylist )
                / ( "BYMONTHDAY" "=" bymodaylist )
                / ( "BYYEARDAY" "=" byyrdaylist )
                / ( "BYWEEKNO" "=" bywknolist )
                / ( "BYMONTH" "=" bymolist )
                / ( "BYSETPOS" "=" bysplist )
                / ( "WKST" "=" weekday )

freq        = "SECONDLY" / "MINUTELY" / "HOURLY" / "DAILY"
            / "WEEKLY" / "MONTHLY" / "YEARLY"

enddate     = date / date-time

byseclist   = ( seconds *("," seconds) )

seconds     = 1*2DIGIT       ;0 to 60

byminlist   = ( minutes *("," minutes) )

minutes     = 1*2DIGIT       ;0 to 59

byhrlist    = ( hour *("," hour) )

hour        = 1*2DIGIT       ;0 to 23

bywdaylist  = ( weekdaynum *("," weekdaynum) )

weekdaynum  = [[plus / minus] ordwk] weekday

plus        = "+"

minus       = "-"

ordwk       = 1*2DIGIT       ;1 to 53

weekday     = "SU" / "MO" / "TU" / "WE" / "TH" / "FR" / "SA"
;Corresponding to SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY,
;FRIDAY, and SATURDAY days of the week.
bymodaylist = ( monthdaynum *("," monthdaynum) )

monthdaynum = [plus / minus] ordmoday

ordmoday    = 1*2DIGIT       ;1 to 31

byyrdaylist = ( yeardaynum *("," yeardaynum) )

yeardaynum  = [plus / minus] ordyrday

ordyrday    = 1*3DIGIT      ;1 to 366

bywknolist  = ( weeknum *("," weeknum) )

weeknum     = [plus / minus] ordwk

bymolist    = ( monthnum *("," monthnum) )

monthnum    = 1*2DIGIT       ;1 to 12

bysplist    = ( setposday *("," setposday) )

setposday   = yeardaynum
```

[3.3.11. Text](https://icalendar.org/iCalendar-RFC-5545/3-3-11-text.html)

```
ESCAPED-CHAR = ("\\" / "\;" / "\," / "\N" / "\n")
   ; \\ encodes \, \N or \n encodes newline
   ; \; encodes ;, \, encodes ,

TSAFE-CHAR = WSP / %x21 / %x23-2B / %x2D-39 / %x3C-5B /
             %x5D-7E / NON-US-ASCII
   ; Any character except CONTROLs not needed by the current
   ; character set, DQUOTE, ";", ":", "\", ","
```

[3.3.12. Time](https://icalendar.org/iCalendar-RFC-5545/3-3-12-time.html)

```
time         = time-hour time-minute time-second [time-utc]

time-hour    = 2DIGIT        ;00-23
time-minute  = 2DIGIT        ;00-59
time-second  = 2DIGIT        ;00-60
;The "60" value is used to account for positive "leap" seconds.

time-utc     = "Z"
```

[3.3.13. URI](https://icalendar.org/iCalendar-RFC-5545/3-3-13-uri.html)

```
uri = ???
```

[3.3.14. UTC Offset](https://icalendar.org/iCalendar-RFC-5545/3-3-14-utc-offset.html)

```
utc-offset = time-numzone

time-numzone = ("+" / "-") time-hour time-minute [time-second]
```

[3.4. iCalendar Object](https://icalendar.org/iCalendar-RFC-5545/3-4-icalendar-object.html)

```
icalstream = 1*icalobject

icalobject = "BEGIN" ":" "VCALENDAR" CRLF
             icalbody
             "END" ":" "VCALENDAR" CRLF
```

[3.6. Calendar Components](https://icalendar.org/iCalendar-RFC-5545/3-6-calendar-components.html)

```
icalbody   = calprops component

calprops   = *(
           ;
           ; The following are REQUIRED,
           ; but MUST NOT occur more than once.
           ;
           prodid / version /
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           calscale / method /
           ;
           ; The following are OPTIONAL,
           ; and MAY occur more than once.
           ;
           x-prop / iana-prop
           ;
           )

component  = 1*(eventc / todoc / journalc / freebusyc /
             timezonec / iana-comp / x-comp)

iana-comp  = "BEGIN" ":" iana-token CRLF
             1*contentline
             "END" ":" iana-token CRLF

x-comp     = "BEGIN" ":" x-name CRLF
             1*contentline
             "END" ":" x-name CRLF
```

[3.6.1. Event Component](https://icalendar.org/iCalendar-RFC-5545/3-6-1-event-component.html)

```
eventc     = "BEGIN" ":" "VEVENT" CRLF
             eventprop *alarmc
             "END" ":" "VEVENT" CRLF

eventprop  = *(
           ;
           ; The following are REQUIRED,
           ; but MUST NOT occur more than once.
           ;
           dtstamp / uid /
           ;
           ; The following is REQUIRED if the component
           ; appears in an iCalendar object that doesn't
           ; specify the "METHOD" property; otherwise, it
           ; is OPTIONAL; in any case, it MUST NOT occur
           ; more than once.
           ;
           dtstart /
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           class / created / description / geo /
           last-mod / location / organizer / priority /
           seq / status / summary / transp /
           url / recurid /
           ;
           ; The following is OPTIONAL,
           ; but SHOULD NOT occur more than once.
           ;
           rrule /
           ;
           ; Either 'dtend' or 'duration' MAY appear in
           ; a 'eventprop', but 'dtend' and 'duration'
           ; MUST NOT occur in the same 'eventprop'.
           ;
           dtend / duration /
           ;
           ; The following are OPTIONAL,
           ; and MAY occur more than once.
           ;
           attach / attendee / categories / comment /
           contact / exdate / rstatus / related /
           resources / rdate / x-prop / iana-prop
           ;
           )
```

[3.6.2. To-Do Component](https://icalendar.org/iCalendar-RFC-5545/3-6-2-to-do-component.html)

```
todoc      = "BEGIN" ":" "VTODO" CRLF
             todoprop *alarmc
             "END" ":" "VTODO" CRLF

todoprop   = *(
           ;
           ; The following are REQUIRED,
           ; but MUST NOT occur more than once.
           ;
           dtstamp / uid /
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           class / completed / created / description /
           dtstart / geo / last-mod / location / organizer /
           percent / priority / recurid / seq / status /
           summary / url /
           ;
           ; The following is OPTIONAL,
           ; but SHOULD NOT occur more than once.
           ;
           rrule /
           ;
           ; Either 'due' or 'duration' MAY appear in
           ; a 'todoprop', but 'due' and 'duration'
           ; MUST NOT occur in the same 'todoprop'.
           ; If 'duration' appear in a 'todoprop',
           ; then 'dtstart' MUST also appear in
           ; the same 'todoprop'.
           ;
           due / duration /
           ;
           ; The following are OPTIONAL,
           ; and MAY occur more than once.
           ;
           attach / attendee / categories / comment / contact /
           exdate / rstatus / related / resources /
           rdate / x-prop / iana-prop
           ;
           )
```

[3.6.3. Journal Component](https://icalendar.org/iCalendar-RFC-5545/3-6-3-journal-component.html)

```
journalc   = "BEGIN" ":" "VJOURNAL" CRLF
             jourprop
             "END" ":" "VJOURNAL" CRLF

jourprop   = *(
           ;
           ; The following are REQUIRED,
           ; but MUST NOT occur more than once.
           ;
           dtstamp / uid /
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           class / created / dtstart /
           last-mod / organizer / recurid / seq /
           status / summary / url /
           ;
           ; The following is OPTIONAL,
           ; but SHOULD NOT occur more than once.
           ;
           rrule /
           ;
           ; The following are OPTIONAL,
           ; and MAY occur more than once.
           ;
           attach / attendee / categories / comment /
           contact / description / exdate / related / rdate /
           rstatus / x-prop / iana-prop
           ;
           )
```

[3.6.4. Free/Busy Component](https://icalendar.org/iCalendar-RFC-5545/3-6-4-free-busy-component.html)

```
freebusyc  = "BEGIN" ":" "VFREEBUSY" CRLF
             fbprop
             "END" ":" "VFREEBUSY" CRLF

fbprop     = *(
           ;
           ; The following are REQUIRED,
           ; but MUST NOT occur more than once.
           ;
           dtstamp / uid /
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           contact / dtstart / dtend /
           organizer / url /
           ;
           ; The following are OPTIONAL,
           ; and MAY occur more than once.
           ;
           attendee / comment / freebusy / rstatus / x-prop /
           iana-prop
           ;
           )
```

[3.6.5. Time Zone Component](https://icalendar.org/iCalendar-RFC-5545/3-6-5-time-zone-component.html)

```
timezonec  = "BEGIN" ":" "VTIMEZONE" CRLF
             *(
             ;
             ; 'tzid' is REQUIRED, but MUST NOT occur more
             ; than once.
             ;
             tzid /
             ;
             ; 'last-mod' and 'tzurl' are OPTIONAL,
             ; but MUST NOT occur more than once.
             ;
             last-mod / tzurl /
             ;
             ; One of 'standardc' or 'daylightc' MUST occur
             ; and each MAY occur more than once.
             ;
             standardc / daylightc /
             ;
             ; The following are OPTIONAL,
             ; and MAY occur more than once.
             ;
             x-prop / iana-prop
             ;
             )
             "END" ":" "VTIMEZONE" CRLF

standardc  = "BEGIN" ":" "STANDARD" CRLF
             tzprop
             "END" ":" "STANDARD" CRLF

daylightc  = "BEGIN" ":" "DAYLIGHT" CRLF
             tzprop
             "END" ":" "DAYLIGHT" CRLF

tzprop     = *(
             ;
             ; The following are REQUIRED,
             ; but MUST NOT occur more than once.
             ;
             dtstart / tzoffsetto / tzoffsetfrom /
             ;
             ; The following is OPTIONAL,
             ; but SHOULD NOT occur more than once.
             ;
             rrule /
             ;
             ; The following are OPTIONAL,
             ; and MAY occur more than once.
             ;
             comment / rdate / tzname / x-prop / iana-prop
             ;
             )
```

[3.6.6. Alarm Component](https://icalendar.org/iCalendar-RFC-5545/3-6-6-alarm-component.html)

```
alarmc     = "BEGIN" ":" "VALARM" CRLF
             (audioprop / dispprop / emailprop)
             "END" ":" "VALARM" CRLF

audioprop  = *(
           ;
           ; 'action' and 'trigger' are both REQUIRED,
           ; but MUST NOT occur more than once.
           ;
           action / trigger /
           ;
           ; 'duration' and 'repeat' are both OPTIONAL,
           ; and MUST NOT occur more than once each;
           ; but if one occurs, so MUST the other.
           ;
           duration / repeat /
           ;
           ; The following is OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           attach /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           x-prop / iana-prop
           ;
           )

dispprop   = *(
           ;
           ; The following are REQUIRED,
           ; but MUST NOT occur more than once.
           ;
           action / description / trigger /
           ;
           ; 'duration' and 'repeat' are both OPTIONAL,
           ; and MUST NOT occur more than once each;
           ; but if one occurs, so MUST the other.
           ;
           duration / repeat /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           x-prop / iana-prop
           ;
           )

emailprop  = *(
           ;
           ; The following are all REQUIRED,
           ; but MUST NOT occur more than once.
           ;
           action / description / trigger / summary /
           ;
           ; The following is REQUIRED,
           ; and MAY occur more than once.
           ;
           attendee /
           ;
           ; 'duration' and 'repeat' are both OPTIONAL,
           ; and MUST NOT occur more than once each;
           ; but if one occurs, so MUST the other.
           ;
           duration / repeat /
           ;
           ; The following are OPTIONAL,
           ; and MAY occur more than once.
           ;
           attach / x-prop / iana-prop
           ;
           )
```

[3.7.1. Calendar Scale](https://icalendar.org/iCalendar-RFC-5545/3-7-1-calendar-scale.html)

```
calscale   = "CALSCALE" calparam ":" calvalue CRLF

calparam   = *(";" other-param)

calvalue   = "GREGORIAN"
```

[3.7.2. Method](https://icalendar.org/iCalendar-RFC-5545/3-7-2-method.html)

```
method     = "METHOD" metparam ":" metvalue CRLF

metparam   = *(";" other-param)

metvalue   = iana-token
```

[3.7.3. Product Identifier](https://icalendar.org/iCalendar-RFC-5545/3-7-3-product-identifier.html)

```
prodid     = "PRODID" pidparam ":" pidvalue CRLF

pidparam   = *(";" other-param)

pidvalue   = text
;Any text that describes the product and version
;and that is generally assured of being unique.
```

[3.7.4. Version](https://icalendar.org/iCalendar-RFC-5545/3-7-4-version.html)

```
version    = "VERSION" verparam ":" vervalue CRLF

verparam   = *(";" other-param)

vervalue   = "2.0"         ;This memo
           / maxver
           / (minver ";" maxver)

minver     = 
;Minimum iCalendar version needed to parse the iCalendar object.

maxver     = 
;Maximum iCalendar version needed to parse the iCalendar object.
```

[3.8.1.1. Attachment](https://icalendar.org/iCalendar-RFC-5545/3-8-1-1-attachment.html)

```
attach     = "ATTACH" attachparam ( ":" uri ) /
             (
               ";" "ENCODING" "=" "BASE64"
               ";" "VALUE" "=" "BINARY"
               ":" binary
             )
             CRL

attachparam = *(
            ;
            ; The following is OPTIONAL for a URI value,
            ; RECOMMENDED for a BINARY value,
            ; and MUST NOT occur more than once.
            ;
            (";" fmttypeparam) /
            ;
            ; The following is OPTIONAL,
            ; and MAY occur more than once.
            ;
            (";" other-param)
            ;
            )
```

[3.8.1.2. Categories](https://icalendar.org/iCalendar-RFC-5545/3-8-1-2-categories.html)

```
categories = "CATEGORIES" catparam ":" text *("," text)
             CRLF

catparam   = *(
           ;
           ; The following is OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" languageparam ) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )
```

[3.8.1.3. Classification](https://icalendar.org/iCalendar-RFC-5545/3-8-1-3-classification.html)

```
class      = "CLASS" classparam ":" classvalue CRLF

classparam = *(";" other-param)

classvalue = "PUBLIC" / "PRIVATE" / "CONFIDENTIAL" / iana-token
           / x-name
;Default is PUBLIC
```

[3.8.1.4. Comment](https://icalendar.org/iCalendar-RFC-5545/3-8-1-4-comment.html)

```
comment    = "COMMENT" commparam ":" text CRLF

commparam  = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" altrepparam) / (";" languageparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )
```

[3.8.1.5. Description](https://icalendar.org/iCalendar-RFC-5545/3-8-1-5-description.html)

```
description = "DESCRIPTION" descparam ":" text CRLF

descparam   = *(
            ;
            ; The following are OPTIONAL,
            ; but MUST NOT occur more than once.
            ;
            (";" altrepparam) / (";" languageparam) /
            ;
            ; The following is OPTIONAL,
            ; and MAY occur more than once.
            ;
            (";" other-param)
            ;
            )
```

[3.8.1.6. Geographic Position](https://icalendar.org/iCalendar-RFC-5545/3-8-1-6-geographic-position.html)

```
geo        = "GEO" geoparam ":" geovalue CRLF

geoparam   = *(";" other-param)

geovalue   = float ";" float
;Latitude and Longitude components
```

[3.8.1.7. Location](https://icalendar.org/iCalendar-RFC-5545/3-8-1-7-location.html)

```
location   = "LOCATION"  locparam ":" text CRLF

locparam   = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" altrepparam) / (";" languageparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )
```

[3.8.1.8. Percent Complete](https://icalendar.org/iCalendar-RFC-5545/3-8-1-8-percent-complete.html)

```
percent = "PERCENT-COMPLETE" pctparam ":" integer CRLF

pctparam   = *(";" other-param)
```

[3.8.1.9. Priority](https://icalendar.org/iCalendar-RFC-5545/3-8-1-9-priority.html)

```
priority   = "PRIORITY" prioparam ":" priovalue CRLF
;Default is zero (i.e., undefined).

prioparam  = *(";" other-param)

priovalue   = integer       ;Must be in the range [0..9]
   ; All other values are reserved for future use.
```

[3.8.1.10. Resources](https://icalendar.org/iCalendar-RFC-5545/3-8-1-10-resources.html)

```
resources  = "RESOURCES" resrcparam ":" text *("," text) CRLF

resrcparam = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" altrepparam) / (";" languageparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )
```

[3.8.1.11. Status](https://icalendar.org/iCalendar-RFC-5545/3-8-1-11-status.html)

```
status          = "STATUS" statparam ":" statvalue CRLF

statparam       = *(";" other-param)

statvalue       = (statvalue-event
                /  statvalue-todo
                /  statvalue-jour)

statvalue-event = "TENTATIVE"    ;Indicates event is tentative.
                / "CONFIRMED"    ;Indicates event is definite.
                / "CANCELLED"    ;Indicates event was cancelled.
;Status values for a "VEVENT"

statvalue-todo  = "NEEDS-ACTION" ;Indicates to-do needs action.
                / "COMPLETED"    ;Indicates to-do completed.
                / "IN-PROCESS"   ;Indicates to-do in process of.
                / "CANCELLED"    ;Indicates to-do was cancelled.
;Status values for "VTODO".

statvalue-jour  = "DRAFT"        ;Indicates journal is draft.
                / "FINAL"        ;Indicates journal is final.
                / "CANCELLED"    ;Indicates journal is removed.
;Status values for "VJOURNAL".
```

[3.8.1.12. Summary](https://icalendar.org/iCalendar-RFC-5545/3-8-1-12-summary.html)

```
summary    = "SUMMARY" summparam ":" text CRLF

summparam  = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" altrepparam) / (";" languageparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )
```

[3.8.2.1. Date-Time Completed](https://icalendar.org/iCalendar-RFC-5545/3-8-2-1-date-time-completed.html)

```
completed  = "COMPLETED" compparam ":" date-time CRLF

compparam  = *(";" other-param)
```

[3.8.2.2. Date-Time End](https://icalendar.org/iCalendar-RFC-5545/3-8-2-2-date-time-end.html)

```
dtendparam = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" "VALUE" "=" ("DATE-TIME" / "DATE")) /
           (";" tzidparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )

dtendval   = date-time / date
;Value MUST match value type
```

[3.8.2.3. Date-Time Due](https://icalendar.org/iCalendar-RFC-5545/3-8-2-3-date-time-due.html)

```
due        = "DUE" dueparam ":" dueval CRLF

dueparam   = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" "VALUE" "=" ("DATE-TIME" / "DATE")) /
           (";" tzidparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )

dueval     = date-time / date
;Value MUST match value type
```

[3.8.2.4. Date-Time Start](https://icalendar.org/iCalendar-RFC-5545/3-8-2-4-date-time-start.html)

```
dtstart    = "DTSTART" dtstparam ":" dtstval CRLF

dtstparam  = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" "VALUE" "=" ("DATE-TIME" / "DATE")) /
           (";" tzidparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )

dtstval    = date-time / date
;Value MUST match value type
```

[3.8.2.5. Duration](https://icalendar.org/iCalendar-RFC-5545/3-8-2-5-duration.html)

```
duration   = "DURATION" durparam ":" dur-value CRLF
             ;consisting of a positive duration of time.

durparam   = *(";" other-param)
```

[3.8.2.6. Free/Busy Time](https://icalendar.org/iCalendar-RFC-5545/3-8-2-6-free-busy-time.html)

```
freebusy   = "FREEBUSY" fbparam ":" fbvalue CRLF

fbparam    = *(
           ;
           ; The following is OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" fbtypeparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )

fbvalue    = period *("," period)
;Time value MUST be in the UTC time format.
```

[3.8.2.7. Time Transparency](https://icalendar.org/iCalendar-RFC-5545/3-8-2-7-time-transparency.html)

```
transp     = "TRANSP" transparam ":" transvalue CRLF

transparam = *(";" other-param)



transvalue = "OPAQUE"
            ;Blocks or opaque on busy time searches.
            / "TRANSPARENT"
            ;Transparent on busy time searches.
;Default value is OPAQUE
Example:  The following is an example of this property for an event
that is transparent or does not block on free/busy time searches:
```

[3.8.3.1. Time Zone Identifier](https://icalendar.org/iCalendar-RFC-5545/3-8-3-1-time-zone-identifier.html)

```
tzid       = "TZID" tzidpropparam ":" [tzidprefix] text CRLF

tzidpropparam      = *(";" other-param)

;tzidprefix        = "/"
; Defined previously. Just listed here for reader convenience.
```

[3.8.3.2. Time Zone Name](https://icalendar.org/iCalendar-RFC-5545/3-8-3-2-time-zone-name.html)

```
tzname     = "TZNAME" tznparam ":" text CRLF

tznparam   = *(
           ;
           ; The following is OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" languageparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )
```

[3.8.3.3. Time Zone Offset From](https://icalendar.org/iCalendar-RFC-5545/3-8-3-3-time-zone-offset-from.html)

```
tzoffsetfrom       = "TZOFFSETFROM" frmparam ":" utc-offset
                     CRLF

frmparam   = *(";" other-param)
```

[3.8.3.4. Time Zone Offset To](https://icalendar.org/iCalendar-RFC-5545/3-8-3-4-time-zone-offset-to.html)

```
tzoffsetto = "TZOFFSETTO" toparam ":" utc-offset CRLF

toparam    = *(";" other-param)
```

[3.8.3.5. Time Zone URL](https://icalendar.org/iCalendar-RFC-5545/3-8-3-5-time-zone-url.html)

```
tzurl      = "TZURL" tzurlparam ":" uri CRLF

tzurlparam = *(";" other-param)
```

[3.8.4.1. Attendee](https://icalendar.org/iCalendar-RFC-5545/3-8-4-1-attendee.html)

```
attendee   = "ATTENDEE" attparam ":" cal-address CRLF

attparam   = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" cutypeparam) / (";" memberparam) /
           (";" roleparam) / (";" partstatparam) /
           (";" rsvpparam) / (";" deltoparam) /
           (";" delfromparam) / (";" sentbyparam) /
           (";" cnparam) / (";" dirparam) /
           (";" languageparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )
```

[3.8.4.2. Contact](https://icalendar.org/iCalendar-RFC-5545/3-8-4-2-contact.html)

```
contact    = "CONTACT" contparam ":" text CRLF

contparam  = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" altrepparam) / (";" languageparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )
```

[3.8.4.3. Organizer](https://icalendar.org/iCalendar-RFC-5545/3-8-4-3-organizer.html)

```
organizer  = "ORGANIZER" orgparam ":"
             cal-address CRLF

orgparam   = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" cnparam) / (";" dirparam) / (";" sentbyparam) /
           (";" languageparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )
```

[3.8.4.4. Recurrence ID](https://icalendar.org/iCalendar-RFC-5545/3-8-4-4-recurrence-id.html)

```
recurid    = "RECURRENCE-ID" ridparam ":" ridval CRLF

ridparam   = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" "VALUE" "=" ("DATE-TIME" / "DATE")) /
           (";" tzidparam) / (";" rangeparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )

ridval     = date-time / date
;Value MUST match value type
```

[3.8.4.5. Related To](https://icalendar.org/iCalendar-RFC-5545/3-8-4-5-related-to.html)

```
related    = "RELATED-TO" relparam ":" text CRLF



relparam   = *(
           ;
           ; The following is OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" reltypeparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )
```

[3.8.4.6. Uniform Resource Locator](https://icalendar.org/iCalendar-RFC-5545/3-8-4-6-uniform-resource-locator.html)

```
url        = "URL" urlparam ":" uri CRLF

urlparam   = *(";" other-param)
```

[3.8.4.7. Unique Identifier](https://icalendar.org/iCalendar-RFC-5545/3-8-4-7-unique-identifier.html)

```
uid        = "UID" uidparam ":" text CRLF

uidparam   = *(";" other-param)
```

[3.8.5.1. Exception Date-Times](https://icalendar.org/iCalendar-RFC-5545/3-8-5-1-exception-date-times.html)

```
exdate     = "EXDATE" exdtparam ":" exdtval *("," exdtval) CRLF

exdtparam  = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" "VALUE" "=" ("DATE-TIME" / "DATE")) /
           ;
           (";" tzidparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )

exdtval    = date-time / date
;Value MUST match value type
```

[3.8.5.2. Recurrence Date-Times](https://icalendar.org/iCalendar-RFC-5545/3-8-5-2-recurrence-date-times.html)

```
rdate      = "RDATE" rdtparam ":" rdtval *("," rdtval) CRLF

rdtparam   = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" "VALUE" "=" ("DATE-TIME" / "DATE" / "PERIOD")) /
           (";" tzidparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )

rdtval     = date-time / date / period
;Value MUST match value type
```

[3.8.5.3. Recurrence Rule](https://icalendar.org/iCalendar-RFC-5545/3-8-5-3-recurrence-rule.html)

```
rrule      = "RRULE" rrulparam ":" recur CRLF

rrulparam  = *(";" other-param)
```

[3.8.6.1. Action](https://icalendar.org/iCalendar-RFC-5545/3-8-6-1-action.html)

```
action      = "ACTION" actionparam ":" actionvalue CRLF

actionparam = *(";" other-param)
```

[3.8.6.2. Repeat Count](https://icalendar.org/iCalendar-RFC-5545/3-8-6-2-repeat-count.html)

```
repeat  = "REPEAT" repparam ":" integer CRLF
;Default is "0", zero.

repparam   = *(";" other-param)
```

[3.8.6.3. Trigger](https://icalendar.org/iCalendar-RFC-5545/3-8-6-3-trigger.html)

```
trigger    = "TRIGGER" (trigrel / trigabs) CRLF

trigrel    = *(
           ;
           ; The following are OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" "VALUE" "=" "DURATION") /
           (";" trigrelparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
               ;
           ) ":"  dur-value

trigabs    = *(
           ;
           ; The following is REQUIRED,
           ; but MUST NOT occur more than once.
           ;
           (";" "VALUE" "=" "DATE-TIME") /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           ) ":" date-time
```

[3.8.7.1. Date-Time Created](https://icalendar.org/iCalendar-RFC-5545/3-8-7-1-date-time-created.html)

```
created    = "CREATED" creaparam ":" date-time CRLF

creaparam  = *(";" other-param)
```

[3.8.7.2. Date-Time Stamp](https://icalendar.org/iCalendar-RFC-5545/3-8-7-2-date-time-stamp.html)

```
dtstamp    = "DTSTAMP" stmparam ":" date-time CRLF

stmparam   = *(";" other-param)
```

[3.8.7.3. Last Modified](https://icalendar.org/iCalendar-RFC-5545/3-8-7-3-last-modified.html)

```
last-mod   = "LAST-MODIFIED" lstparam ":" date-time CRLF

lstparam   = *(";" other-param)
```

[3.8.7.4. Sequence Number](https://icalendar.org/iCalendar-RFC-5545/3-8-7-4-sequence-number.html)

```
seq = "SEQUENCE" seqparam ":" integer CRLF
; Default is "0"

seqparam   = *(";" other-param)
```

[3.8.8.1. IANA Properties](https://icalendar.org/iCalendar-RFC-5545/3-8-8-1-iana-properties.html)

```
iana-prop = iana-token *(";" icalparameter) ":" value CRLF
```

[3.8.8.2. Non-Standard Properties](https://icalendar.org/iCalendar-RFC-5545/3-8-8-2-non-standard-properties.html)

```
x-prop = x-name *(";" icalparameter) ":" value CRLF
```

[3.8.8.3. Request Status](https://icalendar.org/iCalendar-RFC-5545/3-8-8-3-request-status.html)

```
rstatus    = "REQUEST-STATUS" rstatparam ":"
             statcode ";" statdesc [";" extdata]

rstatparam = *(
           ;
           ; The following is OPTIONAL,
           ; but MUST NOT occur more than once.
           ;
           (";" languageparam) /
           ;
           ; The following is OPTIONAL,
           ; and MAY occur more than once.
           ;
           (";" other-param)
           ;
           )

statcode   = 1*DIGIT 1*2("." 1*DIGIT)
;Hierarchical, numeric return status code

statdesc   = text
;Textual status description

extdata    = text
;Textual exception data.  For example, the offending property
;name and value or complete property line.
```
